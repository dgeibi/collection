const RR = require('../rr')
const PCB = require('../PCB')
const { tlog } = require('../../util')
const { clone } = require('../helper')

const pending = PCB.random(5)
const g = [
  new RR({ pending: clone(pending), sliceNum: 1 }),
  new RR({ pending, sliceNum: 4 }),
]

tlog(
  [
    g.map(x => `${x.constructor.name} sliceNum#${x.sliceNum}`),
    g.map(x =>
      x
        .run()
        .printLogs()
        .avgTime()
    ),
  ],
  'avg'
)
