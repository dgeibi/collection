const { maybeUndefined } = require('./util')

let uupid = 0
function getPid() {
  uupid += 1
  return `_${uupid}`
}
class PCB {
  constructor(opt = {}) {
    const { needTime, arriveTime, pid, job } = opt
    this.pid = maybeUndefined(pid, getPid)
    this.maxNeedTime = needTime
    this.needTime = this.maxNeedTime
    this.arriveTime = arriveTime
    this.finishedTime = NaN
    this.cyclingTime = NaN
    this.job = job
    this.state = PCB.stateType.WAIT
  }

  tick() {
    if (this.needTime > 0) {
      this.state = PCB.stateType.RUN
      this.needTime -= 1
      if (this.needTime <= 0) {
        this.state = PCB.stateType.FINISH
      }
    } else {
      this.state = PCB.stateType.FINISH
    }
  }

  stop() {
    if (this.state === PCB.stateType.RUN) {
      this.state = PCB.stateType.WAIT
    }
  }

  isFinished() {
    return this.state === PCB.stateType.FINISH
  }

  kill() {
    this.job = null
  }
}

PCB.stateType = {
  WAIT: 'WAITTING',
  RUN: 'RUNNING',
  FINISH: 'FINISHED',
}

module.exports = PCB
