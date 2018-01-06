/* IMPORTANT
 * This snapshot file is auto-generated, but designed for humans.
 * It should be checked into source control and tracked carefully.
 * Re-generate by setting TAP_SNAPSHOT=1 and running tests.
 * Make sure to inspect the output below.  Do not ignore changes!
 */
'use strict'
exports[`test/ps-rr-schedule.js TAP > ps ready | T0 1`] = `
[ PCB {
    pid: '_1',
    maxNeedTime: 5,
    needTime: 5,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 1,
       memSize: 100,
       needTime: 5,
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
                  address: 300,
                  size: 340,
                  next: null,
                  prev: null,
                  state: 0,
                  job: null,
                  holder: [Circular] } } } ],
       pcbs: [ [Circular] ] },
    state: 'WAITTING' },
  PCB {
    pid: '_2',
    maxNeedTime: 2,
    needTime: 2,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
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
                  address: 300,
                  size: 340,
                  next: null,
                  prev: null,
                  state: 0,
                  job: null,
                  holder: [Circular] } } } ],
       pcbs: [ [Circular] ] },
    state: 'WAITTING' },
  PCB {
    pid: '_3',
    maxNeedTime: 4,
    needTime: 4,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 3,
       memSize: 100,
       needTime: 4,
       arriveTime: 0,
       loadedTime: 0,
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
                  address: 300,
                  size: 340,
                  next: null,
                  prev: null,
                  state: 0,
                  job: null,
                  holder: [Circular] } } } ],
       pcbs: [ [Circular] ] },
    state: 'WAITTING' } ]
`

exports[`test/ps-rr-schedule.js TAP > ps dead | T0 1`] = `
[]
`

exports[`test/ps-rr-schedule.js TAP > ps ready | T3 1`] = `
[ PCB {
    pid: '_2',
    maxNeedTime: 2,
    needTime: 2,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
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
                  address: 300,
                  size: 340,
                  next: null,
                  prev: null,
                  state: 0,
                  job: null,
                  holder: [Circular] } } } ],
       pcbs: [ [Circular] ] },
    state: 'WAITTING' },
  PCB {
    pid: '_3',
    maxNeedTime: 4,
    needTime: 4,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 3,
       memSize: 100,
       needTime: 4,
       arriveTime: 0,
       loadedTime: 0,
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
                  address: 300,
                  size: 340,
                  next: null,
                  prev: null,
                  state: 0,
                  job: null,
                  holder: [Circular] } } } ],
       pcbs: [ [Circular] ] },
    state: 'WAITTING' },
  PCB {
    pid: '_1',
    maxNeedTime: 5,
    needTime: 2,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 1,
       memSize: 100,
       needTime: 5,
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
                  address: 300,
                  size: 340,
                  next: null,
                  prev: null,
                  state: 0,
                  job: null,
                  holder: [Circular] } } } ],
       pcbs: [ [Circular] ] },
    state: 'WAITTING' } ]
`

exports[`test/ps-rr-schedule.js TAP > ps dead | T3 1`] = `
[]
`

exports[`test/ps-rr-schedule.js TAP > ps ready | T5 1`] = `
[ PCB {
    pid: '_3',
    maxNeedTime: 4,
    needTime: 4,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 3,
       memSize: 100,
       needTime: 4,
       arriveTime: 0,
       loadedTime: 0,
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
                  address: 100,
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
       pcbs: [ [Circular] ] },
    state: 'WAITTING' },
  PCB {
    pid: '_1',
    maxNeedTime: 5,
    needTime: 2,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 1,
       memSize: 100,
       needTime: 5,
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
       pcbs: [ [Circular] ] },
    state: 'WAITTING' } ]
`

exports[`test/ps-rr-schedule.js TAP > ps dead | T5 1`] = `
[ PCB {
    pid: '_2',
    maxNeedTime: 2,
    needTime: 0,
    arriveTime: 0,
    finishedTime: 5,
    cyclingTime: 5,
    job: null,
    state: 'FINISHED' } ]
`

exports[`test/ps-rr-schedule.js TAP > ps ready | T8 1`] = `
[ PCB {
    pid: '_1',
    maxNeedTime: 5,
    needTime: 2,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 1,
       memSize: 100,
       needTime: 5,
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
       pcbs: [ [Circular] ] },
    state: 'WAITTING' },
  PCB {
    pid: '_3',
    maxNeedTime: 4,
    needTime: 1,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 3,
       memSize: 100,
       needTime: 4,
       arriveTime: 0,
       loadedTime: 0,
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
                  address: 100,
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
       pcbs: [ [Circular] ] },
    state: 'WAITTING' } ]
`

exports[`test/ps-rr-schedule.js TAP > ps dead | T8 1`] = `
[ PCB {
    pid: '_2',
    maxNeedTime: 2,
    needTime: 0,
    arriveTime: 0,
    finishedTime: 5,
    cyclingTime: 5,
    job: null,
    state: 'FINISHED' } ]
`

exports[`test/ps-rr-schedule.js TAP > ps ready | T10 1`] = `
[ PCB {
    pid: '_3',
    maxNeedTime: 4,
    needTime: 1,
    arriveTime: 0,
    finishedTime: NaN,
    cyclingTime: NaN,
    job: 
     JCB {
       jid: 3,
       memSize: 100,
       needTime: 4,
       arriveTime: 0,
       loadedTime: 0,
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
       pcbs: [ [Circular] ] },
    state: 'WAITTING' } ]
`

exports[`test/ps-rr-schedule.js TAP > ps dead | T10 1`] = `
[ PCB {
    pid: '_2',
    maxNeedTime: 2,
    needTime: 0,
    arriveTime: 0,
    finishedTime: 5,
    cyclingTime: 5,
    job: null,
    state: 'FINISHED' },
  PCB {
    pid: '_1',
    maxNeedTime: 5,
    needTime: 0,
    arriveTime: 0,
    finishedTime: 10,
    cyclingTime: 10,
    job: null,
    state: 'FINISHED' } ]
`

exports[`test/ps-rr-schedule.js TAP > ps ready | T11 1`] = `
[]
`

exports[`test/ps-rr-schedule.js TAP > ps dead | T11 1`] = `
[ PCB {
    pid: '_2',
    maxNeedTime: 2,
    needTime: 0,
    arriveTime: 0,
    finishedTime: 5,
    cyclingTime: 5,
    job: null,
    state: 'FINISHED' },
  PCB {
    pid: '_1',
    maxNeedTime: 5,
    needTime: 0,
    arriveTime: 0,
    finishedTime: 10,
    cyclingTime: 10,
    job: null,
    state: 'FINISHED' },
  PCB {
    pid: '_3',
    maxNeedTime: 4,
    needTime: 0,
    arriveTime: 0,
    finishedTime: 11,
    cyclingTime: 11,
    job: null,
    state: 'FINISHED' } ]
`
