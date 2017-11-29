const Base = require('./Base')

class CSCAN extends Base {
  schedule() {
    this.reqs.sort((a, b) => a.track > b.track)

    let index = null

    if (this.edge) {
      index = this.isOutgoing() ? 0 : this.reqs.length - 1
    } else {
      let bigger = null
      let bgI = null
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
    }
    if (
      (this.isOutgoing() && index === this.reqs.length - 1) ||
      (!this.isOutgoing() && index === 0)
    ) {
      this.edge = true
    } else {
      this.edge = false
    }

    return index
  }
}
module.exports = CSCAN
