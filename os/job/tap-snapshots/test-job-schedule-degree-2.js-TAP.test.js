/* IMPORTANT
 * This snapshot file is auto-generated, but designed for humans.
 * It should be checked into source control and tracked carefully.
 * Re-generate by setting TAP_SNAPSHOT=1 and running tests.
 * Make sure to inspect the output below.  Do not ignore changes!
 */
'use strict'
exports[`test/job-schedule-degree-2.js TAP > arrived | T0 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 3,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 0,
         size: 100,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 200,
               size: 440,
               next: null,
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_1',
         maxNeedTime: 3,
         needTime: 3,
         arriveTime: 0,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] },
  JCB {
    jid: 2,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 100,
         size: 100,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 200,
               size: 440,
               next: null,
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_2',
         maxNeedTime: 2,
         needTime: 2,
         arriveTime: 0,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] },
  JCB {
    jid: 3,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: NaN,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'STANDBY',
    partitions: [],
    pcbs: [] } ]
`

exports[`test/job-schedule-degree-2.js TAP > dead | T0 1`] = `
[]
`

exports[`test/job-schedule-degree-2.js TAP > arrived | T3 1`] = `
[ JCB {
    jid: 2,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 100,
         size: 100,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 0,
               size: 100,
               next: 
                MemPartition {
                  address: 300,
                  size: 340,
                  next: null,
                  prev: [Circular],
                  state: 0,
                  job: null,
                  holder: [Circular] },
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_2',
         maxNeedTime: 2,
         needTime: 2,
         arriveTime: 0,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] },
  JCB {
    jid: 3,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 3,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 200,
         size: 100,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 0,
               size: 100,
               next: 
                MemPartition {
                  address: 300,
                  size: 340,
                  next: null,
                  prev: [Circular],
                  state: 0,
                  job: null,
                  holder: [Circular] },
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_3',
         maxNeedTime: 2,
         needTime: 2,
         arriveTime: 3,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] } ]
`

exports[`test/job-schedule-degree-2.js TAP > dead | T3 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 3,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 3,
    cyclingTime: 3,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`

exports[`test/job-schedule-degree-2.js TAP > arrived | T5 1`] = `
[ JCB {
    jid: 3,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 3,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 200,
         size: 100,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 0,
               size: 200,
               next: 
                MemPartition {
                  address: 300,
                  size: 340,
                  next: null,
                  prev: [Circular],
                  state: 0,
                  job: null,
                  holder: [Circular] },
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_3',
         maxNeedTime: 2,
         needTime: 2,
         arriveTime: 3,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] } ]
`

exports[`test/job-schedule-degree-2.js TAP > dead | T5 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 3,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 3,
    cyclingTime: 3,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 2,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 5,
    cyclingTime: 5,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`

exports[`test/job-schedule-degree-2.js TAP > arrived | T7 1`] = `
[]
`

exports[`test/job-schedule-degree-2.js TAP > dead | T7 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 3,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 3,
    cyclingTime: 3,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 2,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 5,
    cyclingTime: 5,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 3,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 3,
    finishedTime: 7,
    cyclingTime: 7,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`
