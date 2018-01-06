/* IMPORTANT
 * This snapshot file is auto-generated, but designed for humans.
 * It should be checked into source control and tracked carefully.
 * Re-generate by setting TAP_SNAPSHOT=1 and running tests.
 * Make sure to inspect the output below.  Do not ignore changes!
 */
'use strict'
exports[`test/job-schedule-basic.js TAP > arrived | T0 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 1,
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
               address: 100,
               size: 540,
               next: null,
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_1',
         maxNeedTime: 1,
         needTime: 1,
         arriveTime: 0,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] } ]
`

exports[`test/job-schedule-basic.js TAP > dead | T0 1`] = `
[]
`

exports[`test/job-schedule-basic.js TAP > arrived | T1 1`] = `
[]
`

exports[`test/job-schedule-basic.js TAP > dead | T1 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 1,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 1,
    cyclingTime: 1,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`

exports[`test/job-schedule-basic.js TAP > arrived | T2 1`] = `
[ JCB {
    jid: 2,
    memSize: 100,
    needTime: 2,
    arriveTime: 2,
    loadedTime: 2,
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
               address: 100,
               size: 540,
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
         arriveTime: 2,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] } ]
`

exports[`test/job-schedule-basic.js TAP > dead | T2 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 1,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 1,
    cyclingTime: 1,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`

exports[`test/job-schedule-basic.js TAP > arrived | T4 1`] = `
[]
`

exports[`test/job-schedule-basic.js TAP > dead | T4 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 1,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 1,
    cyclingTime: 1,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 2,
    memSize: 100,
    needTime: 2,
    arriveTime: 2,
    loadedTime: 2,
    finishedTime: 4,
    cyclingTime: 2,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`
