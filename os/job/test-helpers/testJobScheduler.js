const tap = require('tap')
const runJobScheduler = require('./runJobScheduler')

module.exports = function testJobScheduler(scheduler) {
  return runJobScheduler(scheduler, function matchSnapshot(time) {
    tap.matchSnapshot(scheduler.arrived, `arrived | T${time}`)
    tap.matchSnapshot(scheduler.dead, `dead | T${time}`)
  })
}
