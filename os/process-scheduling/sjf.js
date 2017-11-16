const PCB = require('./PCB')
const Base = require('./base')

class SJFScheduler extends Base {
  /**
   * 短作业优先
   * @param {PCB} a
   * @param {PCB} b
   */
  static sjf(a, b) {
    return a.needTime > b.needTime
  }

  schedule() {
    this.ready.sort(SJFScheduler.sjf)
    return this.ready[0]
  }
}

module.exports = SJFScheduler
