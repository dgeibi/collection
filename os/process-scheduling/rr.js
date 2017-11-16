const stateType = require('./stateType')
const PCB = require('./PCB')
const Base = require('./base')

class RRScheduler extends Base {
  static random(number) {
    const pending = []
    for (let i = 0; i < number; i += 1) {
      pending[i] = new PCB()
    }
    return new RRScheduler({ pending, sliceNum: 3 })
  }

  schedule() {
    return this.ready[0]
  }

  afterRun(proc) {
    if (proc.state === stateType.WAIT) {
      this.ready.push(this.ready.shift())
    }
  }
}

module.exports = RRScheduler
