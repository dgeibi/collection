const JCB = require('./JCB')
const PCB = require('./PCB')
const RRProcessScheduler = require('./RRProcessScheduler')
const MemPartition = require('./MemPartition')
const { maybeUndefined } = require('./util')

class FCFSJobScheduler {
  constructor({ jcbs, degree, rrSlice, maxMemSize } = {}) {
    /** @type {Array<JCB>} */
    this.pending =
      (jcbs &&
        jcbs.map((x, i) => {
          if (x.jid === undefined) return new JCB(Object.assign({ jid: i + 1 }, x))
          return new JCB(x)
        })) ||
      []

    /** @type {Array<JCB>} */
    this.arrived = []

    /** @type {Array<JCB>} */
    this.dead = []

    /** @type {number} 度 */
    this.degree = maybeUndefined(degree, Infinity)

    /** @type {number} 运行中的作业数 */
    this.runningCnt = 0

    /** @type {RRProcessScheduler} 进程调度器 */
    this.psScheduler = new RRProcessScheduler(rrSlice)

    this.memoryHolder = {}
    this.memoryHolder.memory = new MemPartition({
      size: maybeUndefined(maxMemSize, 640),
      holder: this.memoryHolder,
    })
  }

  /**
   * @param {number} time
   * @returns {number} newTime
   */
  run(time) {
    return this.psScheduler.run(time, (newTime, pcb) => {
      if (pcb && pcb.job.isFinished()) {
        const { job } = pcb
        job.kill()
        job.finishedTime = newTime
        job.cyclingTime = newTime - job.arriveTime
        this.removeJob(job)
      }
      this.loadJob(newTime)
      return newTime
    })
  }

  removeJob(job) {
    const index = this.arrived.indexOf(job)
    if (index > -1) {
      this.arrived.splice(index, 1)
      this.runningCnt -= 1
      this.dead.push(job)
    }
    return job
  }

  takeJob(time) {
    const arrived = []
    for (let i = this.pending.length - 1; i >= 0; i -= 1) {
      const job = this.pending[i]
      if (job.arriveTime <= time) {
        arrived.push(this.pending.splice(i, 1)[0])
      }
    }
    for (let i = arrived.length - 1; i >= 0; i -= 1) {
      this.arrived.push(arrived[i])
    }
  }

  loadJob(time) {
    this.takeJob(time)
    // 装入作业
    for (let i = 0; i < this.arrived.length && this.runningCnt < this.degree; i++) {
      const job = this.arrived[i]
      if (job.state === JCB.stateType.STANDBY && job.request(this.memoryHolder.memory)) {
        job.state = JCB.stateType.RUNNING
        if (Number.isNaN(job.loadedTime)) {
          job.loadedTime = time
        }
        this.runningCnt += 1
        const ps = new PCB({
          arriveTime: time,
          needTime: job.needTime,
          job,
        })
        this.psScheduler.loadPS(ps)
        job.pcbs.push(ps)
      }
    }
  }
}

module.exports = FCFSJobScheduler