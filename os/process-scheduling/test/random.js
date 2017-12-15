const HRRN = require('../hrrn')
const SJF = require('../sjf')
const RR = require('../rr')
const PCB = require('../PCB')
const { tlog } = require('../../util')

const { clone } = require('../helper')

const pending = PCB.random(5)
const g = [
  new SJF({ pending: clone(pending) }),
  new RR({ pending: clone(pending), sliceNum: 3 }),
  new HRRN({ pending: clone(pending) }),
]

tlog(
  [
    g.map(x => x.constructor.name),
    g.map(x =>
      x
        .run()
        .printLogs()
        .avgTime()
    ),
  ],
  'avg'
)
