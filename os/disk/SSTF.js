const Base = require('./Base')

class SSTF extends Base {
  // 找到距当前磁头最近的请求磁道
  schedule() {
    const reqs = this.reqs
    let index = 0
    let minDis = Math.abs(reqs[0].track - this.cur)
    reqs.forEach((req, i) => {
      const dis = Math.abs(req.track - this.cur)
      if (dis < minDis) {
        minDis = dis
        index = i
      }
    })
    return index
  }
}

module.exports = SSTF
