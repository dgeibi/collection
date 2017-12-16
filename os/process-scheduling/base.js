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

    while (this.ready.length + this.pending.length > 0) {
      this.takeReady(time)
      if (this.ready.length <= 0) {
        time += 1
        continue
      }
      const proc = this.schedule(time)
      if (!proc) {
        logs.push({ time })
        time += 1
        continue
      }

      const roundTime = Math.min(this.sliceNum, proc.needTime)
      repeat(roundTime, () => proc.tick())
      time += roundTime - 1
      // 快进后，就绪列队要补充
      if (roundTime > 1) {
        this.takeReady(time)
      }

      const log = { time }
      log.running = pickData(proc)
      proc.stop()

      if (proc.state === stateType.FINISH) {
        proc.cyclingTime = time + 1 - proc.arriveTime
        this.dead.push(this.removePs(proc))
      }
      if (this.afterRun) {
        this.afterRun(proc)
      }

      // 记录 time 末的列队
      log.deads = this.dead.map(pickData)
      log.pendings = this.pending.map(pickData)
      log.readys = this.ready.map(pickData)
      logs.push(log)

      time += 1
    }
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
      tlog(log.deads, `${this.constructor.name} Deads Queue of #${log.time}`)
    })
    return this
  }
}

module.exports = Base
