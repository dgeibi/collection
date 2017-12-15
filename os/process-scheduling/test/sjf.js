const assert = require('assert')
const SJF = require('../sjf')
const PCB = require('../PCB')

const pending = (() => {
  const pendings = [
    { arriveTime: 0, needTime: 2 },
    { arriveTime: 0, needTime: 5 },
    { arriveTime: 0, needTime: 1 },
  ]
  return pendings.map((x, i) => new PCB(Object.assign(x, { pid: i + 1 })))
})()

const sl = new SJF({ pending })
sl.run().printLogs()
const proc = sl.logs[0].running
assert(proc.state === 'FINISH')
assert(proc.needTime === 0)
assert(proc.pid === 3)
