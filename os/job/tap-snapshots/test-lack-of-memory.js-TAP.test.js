/* IMPORTANT
 * This snapshot file is auto-generated, but designed for humans.
 * It should be checked into source control and tracked carefully.
 * Re-generate by setting TAP_SNAPSHOT=1 and running tests.
 * Make sure to inspect the output below.  Do not ignore changes!
 */
'use strict'
exports[`test/lack-of-memory.js TAP > arrived | T0 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 2,
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
               address: 110,
               size: 10,
               next: null,
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_1',
         maxNeedTime: 2,
         needTime: 2,
         arriveTime: 0,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] },
  JCB {
    jid: 2,
    memSize: 10,
    needTime: 1,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 100,
         size: 10,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 110,
               size: 10,
               next: null,
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_2',
         maxNeedTime: 1,
         needTime: 1,
         arriveTime: 0,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] },
  JCB {
    jid: 3,
    memSize: 90,
    needTime: 3,
    arriveTime: 0,
    loadedTime: NaN,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'STANDBY',
    partitions: [],
    pcbs: [] } ]
`

exports[`test/lack-of-memory.js TAP > dead | T0 1`] = `
[]
`

exports[`test/lack-of-memory.js TAP > arrived | T2 1`] = `
[ JCB {
    jid: 2,
    memSize: 10,
    needTime: 1,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 100,
         size: 10,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 90,
               size: 10,
               next: 
                MemPartition {
                  address: 110,
                  size: 10,
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
         maxNeedTime: 1,
         needTime: 1,
         arriveTime: 0,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] },
  JCB {
    jid: 3,
    memSize: 90,
    needTime: 3,
    arriveTime: 0,
    loadedTime: 2,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 0,
         size: 90,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 90,
               size: 10,
               next: 
                MemPartition {
                  address: 110,
                  size: 10,
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
         maxNeedTime: 3,
         needTime: 3,
         arriveTime: 2,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] },
  JCB {
    jid: 4,
    memSize: 100,
    needTime: 1,
    arriveTime: 1,
    loadedTime: NaN,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'STANDBY',
    partitions: [],
    pcbs: [] } ]
`

exports[`test/lack-of-memory.js TAP > dead | T2 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 2,
    cyclingTime: 2,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`

exports[`test/lack-of-memory.js TAP > arrived | T3 1`] = `
[ JCB {
    jid: 3,
    memSize: 90,
    needTime: 3,
    arriveTime: 0,
    loadedTime: 2,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'RUNNING',
    partitions: 
     [ MemPartition {
         address: 0,
         size: 90,
         next: null,
         prev: null,
         state: 1,
         job: [Circular],
         holder: 
          { memory: 
             MemPartition {
               address: 90,
               size: 30,
               next: null,
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_3',
         maxNeedTime: 3,
         needTime: 3,
         arriveTime: 2,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] },
  JCB {
    jid: 4,
    memSize: 100,
    needTime: 1,
    arriveTime: 1,
    loadedTime: NaN,
    finishedTime: NaN,
    cyclingTime: NaN,
    state: 'STANDBY',
    partitions: [],
    pcbs: [] } ]
`

exports[`test/lack-of-memory.js TAP > dead | T3 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 2,
    cyclingTime: 2,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 2,
    memSize: 10,
    needTime: 1,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 3,
    cyclingTime: 3,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`

exports[`test/lack-of-memory.js TAP > arrived | T6 1`] = `
[ JCB {
    jid: 4,
    memSize: 100,
    needTime: 1,
    arriveTime: 1,
    loadedTime: 6,
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
               size: 20,
               next: null,
               prev: null,
               state: 0,
               job: null,
               holder: [Circular] } } } ],
    pcbs: 
     [ PCB {
         pid: '_4',
         maxNeedTime: 1,
         needTime: 1,
         arriveTime: 6,
         finishedTime: NaN,
         cyclingTime: NaN,
         job: [Circular],
         state: 'WAITTING' } ] } ]
`

exports[`test/lack-of-memory.js TAP > dead | T6 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 2,
    cyclingTime: 2,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 2,
    memSize: 10,
    needTime: 1,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 3,
    cyclingTime: 3,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 3,
    memSize: 90,
    needTime: 3,
    arriveTime: 0,
    loadedTime: 2,
    finishedTime: 6,
    cyclingTime: 6,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`

exports[`test/lack-of-memory.js TAP > arrived | T7 1`] = `
[]
`

exports[`test/lack-of-memory.js TAP > dead | T7 1`] = `
[ JCB {
    jid: 1,
    memSize: 100,
    needTime: 2,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 2,
    cyclingTime: 2,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 2,
    memSize: 10,
    needTime: 1,
    arriveTime: 0,
    loadedTime: 0,
    finishedTime: 3,
    cyclingTime: 3,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 3,
    memSize: 90,
    needTime: 3,
    arriveTime: 0,
    loadedTime: 2,
    finishedTime: 6,
    cyclingTime: 6,
    state: 'FINISHED',
    partitions: [],
    pcbs: null },
  JCB {
    jid: 4,
    memSize: 100,
    needTime: 1,
    arriveTime: 1,
    loadedTime: 6,
    finishedTime: 7,
    cyclingTime: 6,
    state: 'FINISHED',
    partitions: [],
    pcbs: null } ]
`
