const FFJob = require('./FFJob')
const Partition = require('./Partition')

class BFJob extends FFJob {
  request(size) {
    let ret = false
    let part = Partition.head
    let minSizePart = null
    while (part !== null) {
      if (part.size > size) {
        if (minSizePart === null || minSizePart.size > part.size) {
          minSizePart = part
        }
      }
      part = part.next
    }
    if (minSizePart) {
      // 找到最小的可分配分区并分配
      this.alloc(minSizePart, size)
      ret = true
    }
    this.print(ret, size)
    return ret
  }
}

module.exports = BFJob
