const Scheduler = require('./scheduler')
const PCB = require('./PCB')

const sl = new Scheduler({
  pending: PCB.random(5),
})
sl.run()
