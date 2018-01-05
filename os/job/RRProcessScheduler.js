const PCB = require('./PCB')
const { repeat } = require('./util')

class RRProcessScheduler {
  constructor(sliceNum = 3) {
    /** @type {Array<PCB>} */
    this.ready = []

    /** @type {Array<PCB>} */
    this.dead = []

    /** @type {number} 时间分片大小 */
    this.sliceNum = sliceNum
  }

  run(time, callback) {
    // 调出可运行进程
    const proc = this.ready[0]
    if (!proc) {
      return callback(time + 1)
    }

    // 执行轮数
    const roundTime = Math.min(this.sliceNum, proc.needTime)
    repeat(roundTime, () => proc.tick())
    time += roundTime

    // 修改进程状态
    proc.stop()

    // 若进程已完成，则计算周转时间并移入死亡列队
    if (proc.state === PCB.stateType.FINISH) {
      proc.cyclingTime = time - proc.arriveTime
      proc.finishedTime = time
      this.dead.push(this.removePS(proc))
    }

    const ret = callback(time, proc)

    if (proc.state === PCB.stateType.WAIT) {
      this.ready.push(this.ready.shift())
    }

    return ret
  }

  loadPS(x) {
    this.ready.push(x)
    return x
  }

  removePS(proc) {
    const index = this.ready.indexOf(proc)
    if (index > -1) {
      this.ready.splice(index, 1)
    }
    return proc
  }
}

module.exports = RRProcessScheduler
