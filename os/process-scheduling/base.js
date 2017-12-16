/* eslint-disable no-continue */
const stateType = require('./stateType')
const PCB = require('./PCB') // eslint-disable-line
const { repeat, tlog } = require('../util')

class Base {
  constructor({ pending, ready, sliceNum } = {}) {
    /** @type {Array<PCB>} */
    this.pending = pending || []
    /** @type {Array<PCB>} */
    this.ready = ready || []
    /** @type {Array<PCB>} */
    this.dead = []
    this.sliceNum = sliceNum || 1
    this.logs = null
  }

  run() {
    let time = 0
    const logs = []
    const pickData = x => x.data()
    const pushLog = (time, proc) => {
      logs.push({
        time,
        running: proc && pickData(proc),
        deads: this.dead.map(pickData),
        pendings: this.pending.map(pickData),
        readys: this.ready.map(pickData),
      })
    }
    pushLog('not started')
    // 就绪列队与未到达进程列队长度和大于 0 时循环继续
    while (this.ready.length + this.pending.length > 0) {
      // 将到达的进程移入就绪列队
      this.takeReady(time)

      // 调出可运行进程
      const proc = this.ready.length > 0 && this.schedule(time)
      pushLog(time, proc)

      // 无进程未就绪循环继续
      if (!proc) {
        time += 1
        continue
      }

      // 执行轮数
      const roundTime = Math.min(this.sliceNum, proc.needTime)
      // 执行roundTime轮次
      repeat(roundTime, () => proc.tick())

      time += roundTime

      // 修改进程状态
      proc.stop()

      // 若进程已完成，则计算周转时间并移入死亡列队
      if (proc.state === stateType.FINISH) {
        proc.cyclingTime = time - proc.arriveTime
        proc.finishTime = time
        this.dead.push(this.removePs(proc))
      }

      // 将已运行进程传递给钩子方法
      if (this.afterRun) {
        this.afterRun(proc)
      }
    }

    pushLog(time)
    this.logs = logs
    return this
  }

  removePs(proc) {
    const index = this.ready.indexOf(proc)
    if (index > -1) {
      this.ready.splice(index, 1)
    }
    return proc
  }

  takeReady(time) {
    for (let i = this.pending.length - 1; i >= 0; i -= 1) {
      const proc = this.pending[i]
      if (proc.arriveTime <= time) {
        this.ready.push(this.pending.splice(i, 1)[0])
      }
    }
  }

  avgTime() {
    let deads
    for (let i = this.logs.length - 1; i >= 0; i -= 1) {
      if (this.logs[i].deads) {
        deads = this.logs[i].deads
        break
      }
    }
    return deads ? deads.reduce((sum, pcb) => pcb.cyclingTime + sum, 0) / deads.length : 0
  }

  printLogs() {
    if (!this.logs) return this
    console.log(`${this.constructor.name} running logs:`)
    this.logs.forEach((log) => {
      tlog(log.pendings, `${this.constructor.name} Pendings Queue of #${log.time}`)
      tlog(log.readys, `${this.constructor.name} Ready Queue of #${log.time}`)
      log.running && console.log('----', 'Running', log.running.pid, '----')
      tlog(log.deads, `${this.constructor.name} Deads Queue of #${log.time}`)
    })
    return this
  }
}

module.exports = Base
