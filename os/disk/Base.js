const { tlog } = require('../util')

class Base {
  constructor(reqs, init, direction) {
    this.reqs = reqs
    this.init = init
    this.direction = direction || this.constructor.directions.O
  }

  test() {
    console.log('__', this.constructor.name)
    this.cur = this.init
    const logs = []
    while (this.reqs.length > 0) {
      const index = this.schedule()
      const req = this.reqs[index]
      const { track } = req
      if (req) {
        const distance = Math.abs(req.track - this.cur)
        logs.push({ track, distance })
        this.cur = track
      }
      this.takeout(index)
    }
    this.logs = logs
    tlog(logs)
    console.log('__', 'avg', this.getAvg())
  }

  getAvg() {
    return this.logs.reduce((sum, { distance }) => sum + distance, 0) / this.logs.length
  }

  // eslint-disable-next-line
  schedule() {
    return 0
  }

  takeout(i) {
    const req = this.reqs[i]
    this.reqs.splice(i, 1)
    return req
  }

  isOutgoing() {
    return this.direction === Base.directions.O
  }
}

Base.directions = {
  I: 1,
  O: 2,
}

module.exports = Base
