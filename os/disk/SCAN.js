const Base = require('./Base')

class SCAN extends Base {
  schedule() {
    this.reqs.sort((a, b) => a.track > b.track)
    let bigger = null
    let bgI = null
    let index = null

    for (let i = 0; i < this.reqs.length; i += 1) {
      const req = this.reqs[i]
      if (req.track >= this.cur) {
        bigger = req
        bgI = i
        break
      }
    }

    if (bgI !== null) {
      if (this.isOutgoing() || bgI === 0 || bigger.track === this.cur) {
        index = bgI
      } else {
        index = bgI - 1
      }
    } else {
      index = this.reqs.length - 1
    }

    if (index === this.reqs.length - 1) {
      this.direction = Base.directions.I
    } else if (index === 0) {
      this.direction = Base.directions.O
    }
    return index
  }
}
module.exports = SCAN
