const JobScheduler = require('../FCFSJobScheduler')
const testJobScheduler = require('../test-helpers/testJobScheduler')

const scheduler = new JobScheduler({
  jcbs: [
    { arriveTime: 0, memSize: 100, needTime: 3 },
    { arriveTime: 0, memSize: 100, needTime: 2 },
    { arriveTime: 0, memSize: 100, needTime: 2 },
  ],
  degree: 2,
  rrSlice: 3,
  maxMemSize: 640,
})

testJobScheduler(scheduler)
