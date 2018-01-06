const JobScheduler = require('../FCFSJobScheduler')
const testJobScheduler = require('../test-helpers/testJobScheduler')

const scheduler = new JobScheduler({
  jcbs: [
    { arriveTime: 0, memSize: 100, needTime: 1 },
    { arriveTime: 2, memSize: 100, needTime: 2 },
  ],
  degree: Infinity,
  rrSlice: 3,
  maxMemSize: 640,
})

testJobScheduler(scheduler)
