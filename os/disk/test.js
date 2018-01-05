const Request = require('./Request')
const FCFS = require('./FCFS')
const SSTF = require('./SSTF')
const SCAN = require('./SCAN')
const CSCAN = require('./CSCAN')
const { getRandomInt } = require('../util')

const requests = Array(10)
  .fill(null)
  .map(() => new Request(getRandomInt(0, 200)))

const test = (Fn, ...args) => {
  const scheduler = new Fn(...(args.length > 0 ? args : [requests.slice(), 100]))
  scheduler.test()
}

test(FCFS)
test(SSTF)
test(SCAN)
test(CSCAN)
test(CSCAN, requests.slice(), 100, 1)
