const Base = require('./Base')

class SCAN extends Base {
  schedule() {
    // 寻道请求磁道号从小到大排序
    this.reqs.sort((a, b) => a.track > b.track)

    // 第一个比当前磁道号大或相等的请求
    let bigger = null
    // 对应的请求索引
    let bgI = null

    // 返回值
    let index = null

    for (let i = 0; i < this.reqs.length; i += 1) {
      const req = this.reqs[i]
      if (req.track >= this.cur) {
        bigger = req
        bgI = i
        break
      }
    }

    // 找到磁道号比当前大或相等的
    if (bgI !== null) {
      // 向外移动 或者 索引为0 或者 磁道号相等
      if (this.isOutgoing() || bgI === 0 || bigger.track === this.cur) {
        // 选择最近外面的（或者当前的）
        index = bgI
      } else {
        // 选择最近里面的
        index = bgI - 1
      }
    } else {
      // 未找到，选择最外的
      index = this.reqs.length - 1
    }

    // 改变方向
    if (index === this.reqs.length - 1) {
      this.direction = Base.directions.I
    } else if (index === 0) {
      this.direction = Base.directions.O
    }
    return index
  }
}
module.exports = SCAN
