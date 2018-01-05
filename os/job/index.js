const JobScheduler = require('./FCFSJobScheduler')

const scheduler = new JobScheduler({
  jcbs: [
    { arriveTime: 0, memSize: 100, needTime: 1 },
    { arriveTime: 2, memSize: 100, needTime: 2 },
    { arriveTime: 3, memSize: 100, needTime: 3 },
    { arriveTime: 4, memSize: 100, needTime: 10 },
    { arriveTime: 7, memSize: 100, needTime: 10 },
    { arriveTime: 9, memSize: 100, needTime: 10 },
  ],
})

let time = 0
scheduler.loadJob(time)
while (scheduler.pending.length + scheduler.arrived.length > 0) {
  time = scheduler.run(time)
}
