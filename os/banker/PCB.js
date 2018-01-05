const { getRandomInt, repeat } = require('../util')
const stateType = require('./stateType')
const Res = require('./Res')
const BasePCB = require('../process-scheduling/PCB')

class PCB extends BasePCB {
  constructor({ allocRess, needRess, res, ...superOpt } = {}) {
    super(Object.assign({ arriveTime: 0 }, superOpt))
    if (!needRess) {
      const mres = res || {
        A: getRandomInt(1, 7),
        B: getRandomInt(1, 10),
        C: getRandomInt(1, 9),
      }
      this.needRess = Res.ress(mres)
    } else {
      this.needRess = Res.cloneRess(needRess)
    }
    this.allocRess = allocRess ? Res.cloneRess(allocRess) : Res.ress()
  }

  static random(num) {
    return repeat(num, () => new PCB())
  }

  tick() {
    this.state = stateType.RUN
    Res.adds(this.allocRess, this.reqs)
    Res.reduces(this.needRess, this.reqs)
    if (this.needRess.every(x => x.value <= 0)) {
      this.state = stateType.FINISH
      console.log(this.pid, 'FINISHED')
    }
    this.reqs = null
  }

  block() {
    this.state = stateType.BLOCK
    console.log(this.pid, 'blocked')
  }

  unblock() {
    this.state = stateType.WAIT
  }

  request() {
    this.reqs =
      this.reqs ||
      this.needRess.map(({ value }) => (value > 0 ? getRandomInt(1, value + 1) : 0))
    return this.reqs
  }

  clone() {
    const { needTime, arriveTime, pid, needRess, allocRess } = this
    return new PCB({ needTime, arriveTime, pid, needRess, allocRess })
  }
}

module.exports = PCB
