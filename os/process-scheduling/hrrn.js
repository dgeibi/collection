const PCB = require('./PCB')
const Base = require('./base')

class HRRNScheduler extends Base {
  static random(number) {
    const pending = []
    for (let i = 0; i < number; i += 1) {
      pending[i] = new PCB()
    }
    return new HRRNScheduler({ pending })
  }

  schedule(time) {
    this.ready.forEach(proc => {
      const { needTime, arriveTime } = proc
      proc.priority = (time - arriveTime + needTime) / needTime
    })
    this.ready.sort((a, b) => b.priority > a.priority)
    return this.ready[0]
  }
}

module.exports = HRRNScheduler
