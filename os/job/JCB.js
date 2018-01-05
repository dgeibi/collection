const MemPartition = require('./MemPartition')
const { maybeUndefined } = require('./util')

let uuJID = 0
function getJID() {
  uuJID += 1
  return uuJID
}

class JCB {
  constructor({ arriveTime, jid, memSize, needTime }) {
    this.jid = maybeUndefined(jid, getJID)
    this.memSize = memSize
    this.needTime = needTime
    this.arriveTime = arriveTime
    this.loadedTime = NaN
    this.finishedTime = NaN
    this.cyclingTime = NaN
    this.state = JCB.stateType.STANDBY
    this.partitions = []
    this.pcbs = []
  }

  alloc(part, size) {
    if (part.size - size <= MemPartition.minsize) {
      this.partitions.push(part.remove(this))
    } else {
      this.partitions.push(part.slice(size, this))
    }
  }

  request(size = this.memSize) {
    let part = MemPartition.head
    let ret = false
    while (part !== null && ret === false) {
      if (part.size > size) {
        // 找到第一个适应的分区并分配
        this.alloc(part, size)
        ret = true
      } else {
        part = part.next
      }
    }
    return ret
  }

  release(size = this.memSize) {
    let ret = false
    for (let i = 0; i < this.partitions.length; i += 1) {
      const part = this.partitions[i]
      if (part.size === size) {
        this.partitions.splice(this.partitions.indexOf(part), 1)
        part.mergeInsert()
        ret = true
        break
      }
    }
    return ret
  }

  isFinished() {
    let finished = this.state === JCB.stateType.FINISHED
    if (finished) return finished
    finished = this.pcbs.every(x => x.isFinished())
    if (finished) {
      this.state = JCB.stateType.FINISHED
    }
    return finished
  }

  kill() {
    this.release()
    this.pcbs.forEach(x => x.kill())
    this.pcbs = null
  }
}

JCB.stateType = {
  STANDBY: 'STANDBY',
  RUNNING: 'RUNNING',
  FINISHED: 'FINISHED',
}

module.exports = JCB
