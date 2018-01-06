const JobScheduler = require('../FCFSJobScheduler')
const testJobScheduler = require('../test-helpers/testJobScheduler')

const scheduler = new JobScheduler({
  jcbs: [
    { arriveTime: 0, memSize: 100, needTime: 2 },
    { arriveTime: 0, memSize: 10, needTime: 1 },
    { arriveTime: 0, memSize: 90, needTime: 3 },
    { arriveTime: 1, memSize: 100, needTime: 1 },
  ],
  degree: Infinity,
  rrSlice: 3,
  maxMemSize: 120,
})

testJobScheduler(scheduler)
