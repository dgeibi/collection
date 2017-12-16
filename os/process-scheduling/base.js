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
    pushLog('-0')
    while (this.ready.length + this.pending.length > 0) {
      this.takeReady(time)
      const proc = this.ready.length > 0 && this.schedule(time)
      pushLog(time, proc)

      if (!proc) {
        time += 1
        continue
      }
      const roundTime = Math.min(this.sliceNum, proc.needTime)
      repeat(roundTime, () => proc.tick())
      time += roundTime

      proc.stop()

      if (proc.state === stateType.FINISH) {
        proc.cyclingTime = time - proc.arriveTime
        proc.finishTime = time
        this.dead.push(this.removePs(proc))
      }
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
      tlog(log.deads, `${this.constructor.name} Deads Queue of #${log.time}`)
    })
    return this
  }
}

module.exports = Base
