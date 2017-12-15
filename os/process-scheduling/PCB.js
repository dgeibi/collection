const { getRandomInt, repeat } = require('../util')
const stateType = require('./stateType')

let uupid = 0
function getPid() {
  uupid += 1
  return `_${uupid}`
}
class PCB {
  constructor(opt) {
    const theOpt = Object.assign(
      {
        arriveTime: uupid === 0 ? 0 : getRandomInt(1, 15),
        needTime: getRandomInt(1, 10),
        pid: getPid(),
      },
      opt
    )
    const { needTime, arriveTime, pid } = theOpt
    this.pid = pid
    this.cyclingTime = NaN
    this.priority = NaN
    this.state = stateType.WAIT
    this.needTime = needTime
    this.arriveTime = arriveTime
  }

  static random(num) {
    return repeat(num, () => new PCB())
  }

  tick() {
    if (this.needTime > 0) {
      this.state = stateType.RUN
      this.needTime -= 1
      if (this.needTime <= 0) {
        this.state = stateType.FINISH
      }
    } else {
      this.state = stateType.FINISH
    }
  }

  stop() {
    if (this.state === stateType.RUN) {
      this.state = stateType.WAIT
    }
  }

  data() {
    const data = {}
    // eslint-disable-next-line
    for (const key in this) {
      if (Object.prototype.hasOwnProperty.call(this, key)) {
        const element = this[key]
        data[key] = element
      }
    }
    return data
  }

  clone() {
    const { needTime, arriveTime, pid } = this
    return new PCB({ needTime, arriveTime, pid })
  }
}

module.exports = PCB
