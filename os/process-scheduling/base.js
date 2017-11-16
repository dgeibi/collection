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

    while (time < 1000 && this.ready.length + this.pending.length > 0) {
      this.takeReady(time)
      if (this.ready.length <= 0) {
        time += 1
        continue
      }
      const log = { time }
      const proc = this.schedule(time)
      if (!proc) {
        time += 1
        logs.push(log)
        continue
      }
      const roundTime = Math.min(this.sliceNum, proc.needTime)
      repeat(roundTime, () => proc.tick())
      time += roundTime
      log.running = pickData(proc)
      proc.stop()
      if (proc.state === stateType.FINISH) {
        proc.cyclingTime = time - proc.arriveTime
        this.dead.push(this.removePs(proc))
      }
      if (this.afterRun) {
        this.afterRun(proc)
      }
      log.deads = this.dead.map(pickData)
      log.pendings = this.pending.map(pickData)
      log.readys = this.ready.map(pickData)
      logs.push(log)
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
      if (proc.arriveTime === time) {
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
    if (!this.logs) return
    console.log(`${this.constructor.name} running logs:`)
    this.logs.forEach((log) => {
      console.log(`Pendings Queue of #${log.time}:`)
      tlog(log.pendings)

      console.log(`Ready Queue of #${log.time}:`)
      tlog(log.readys)

      console.log(`Deads Queue of #${log.time}:`)
      tlog(log.deads)
    })
  }
}

module.exports = Base
