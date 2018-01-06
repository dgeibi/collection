const JobScheduler = require('../FCFSJobScheduler')
const testPSScheduler = require('../test-helpers/testPSScheduler')

const scheduler = new JobScheduler({
  jcbs: [
    { arriveTime: 0, memSize: 100, needTime: 5 },
    { arriveTime: 0, memSize: 100, needTime: 2 },
    { arriveTime: 0, memSize: 100, needTime: 4 },
  ],
  degree: Infinity,
  rrSlice: 3,
  maxMemSize: 640,
})

testPSScheduler(scheduler)
