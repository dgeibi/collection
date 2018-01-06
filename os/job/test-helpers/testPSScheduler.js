const tap = require('tap')
const runJobScheduler = require('./runJobScheduler')

module.exports = function testPSScheduler(scheduler) {
  return runJobScheduler(scheduler, function matchSnapshot(time) {
    tap.matchSnapshot(scheduler.psScheduler.ready, `ps ready | T${time}`)
    tap.matchSnapshot(scheduler.psScheduler.dead, `ps dead | T${time}`)
  })
}
