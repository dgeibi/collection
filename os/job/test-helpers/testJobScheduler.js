const tap = require('tap')
const makeJobMatchSnapshot = require('./makeJobMatchSnapshot')

module.exports = (scheduler) => {
  let time = 0
  const matchSnapshot = makeJobMatchSnapshot(tap, () => time)

  scheduler.loadJob(time)
  matchSnapshot(scheduler)
  while (scheduler.pending.length + scheduler.arrived.length > 0) {
    time = scheduler.run(time)
    matchSnapshot(scheduler)
  }
}
