module.exports = function runJobScheduler(scheduler, step) {
  let time = 0

  scheduler.loadJob(time)
  step(time, scheduler)
  while (scheduler.pending.length + scheduler.arrived.length > 0) {
    time = scheduler.run(time)
    step(time, scheduler)
  }
}
