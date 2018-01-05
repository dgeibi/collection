const Base = require('../process-scheduling/base')
const stateType = require('./stateType')
const banker = require('./banker')
const Res = require('./Res')

class RRRScheduler extends Base {
  constructor(opt) {
    super(opt)
    let res = opt && opt.res
    if (res) {
      res = Object.assign({ A: 0, B: 0, C: 0 }, res)
    } else {
      res = { A: 10, B: 15, C: 12 }
    }
    this.avail = Res.ress(res)
  }

  schedule() {
    if (this.ready.length <= 0) return null
    this.ready.forEach(ps => {
      if (
        ps.state === stateType.BLOCK &&
        ps.reqs &&
        ps.reqs.every((x, j) => x <= this.avail[j].value)
      ) {
        // 解除阻塞
        ps.unblock()
      }
    })
    // 需求矩阵
    const need = this.ready.map(ps => ps.needRess)
    // 分配矩阵
    const alloc = this.ready.map(ps => ps.allocRess)

    // 寻找可分配的作业
    for (let i = 0; i < this.ready.length; i += 1) {
      if (this.ready[i].state === stateType.WAIT) {
        const proc = this.ready[i]
        const reqs = proc.request()
        const action = banker({
          i,
          reqs,
          alloc,
          need,
          avail: this.avail,
        })

        if (action === banker.returnType.BLOCK) {
          proc.block()
        } else if (action === banker.returnType.OK) {
          // 消耗资源
          this.consume(reqs)
          console.log(proc.pid, 'consume', reqs)
          return proc
        }
      }
    }
    console.log(this.avail)
    throw Error('Sorry I dead locked')
  }

  /**
   * @param {number[]|Res[]} ress
   */
  consume(ress) {
    Res.reduces(this.avail, ress)
  }

  /**
   * @param {number[]|Res[]} ress
   */
  recycle(ress) {
    Res.adds(this.avail, ress)
  }

  afterRun(proc) {
    if (proc.state === stateType.WAIT) {
      this.ready.push(this.removePs(proc))
    } else if (proc.state === stateType.FINISH) {
      this.recycle(proc.allocRess)
      console.log(JSON.stringify(this.avail))
    }
  }
}

module.exports = RRRScheduler
