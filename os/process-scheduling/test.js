const assert = require('assert')
const HRRN = require('./hrrn')
const SJF = require('./sjf')
const RR = require('./rr')
const PCB = require('./PCB')
const { tlog } = require('../util')

const clone = pcbs => pcbs.map(x => x.clone())

{
  const pending = PCB.random(5)
  const g = [
    new HRRN({ pending: clone(pending) }),
    new SJF({ pending: clone(pending) }),
    new RR({ pending: clone(pending), sliceNum: 3 }),
  ]
  tlog([g.map(x => x.constructor.name), g.map(x => x.run().avgTime())])
}

{
  const pending = PCB.random(5)
  const g = [new RR({ pending: clone(pending), sliceNum: 1 }), new RR({ pending, sliceNum: 4 })]
  tlog([g.map(x => `${x.constructor.name} sliceNum#${x.sliceNum}`), g.map(x => x.run().avgTime())])
}

{
  const conPendings = () => {
    const pendings = [
      { arriveTime: 0, needTime: 2 },
      { arriveTime: 0, needTime: 5 },
      { arriveTime: 0, needTime: 1 },
    ]
    return pendings.map((x, i) => new PCB(Object.assign(x, { pid: i + 1 })))
  }

  {
    const sl = new SJF({ pending: conPendings() })
    sl.run().printLogs()
    const proc = sl.logs[0].running
    assert(proc.state === 'FINISH')
    assert(proc.needTime === 0)
    assert(proc.pid === 3)
  }
}
