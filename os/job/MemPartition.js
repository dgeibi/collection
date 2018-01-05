const { maybeUndefined } = require('./util')

class MemPartition {
  constructor({ address, size, next, prev, job, state } = {}) {
    /** @type {number} */
    this.address = maybeUndefined(address, 0)

    /** @type {number} */
    this.size = maybeUndefined(size, 0)

    /** @type {MemPartition} */
    this.next = maybeUndefined(next, null)

    /** @type {MemPartition} */
    this.prev = maybeUndefined(prev, null)

    /** @type {number} */
    this.state = maybeUndefined(state, MemPartition.stateType.FREE)

    this.job = maybeUndefined(job, null)
  }

  unlink() {
    this.prev = null
    this.next = null
  }

  merge() {
    const { next } = this
    if (next && this.address + this.size === next.address) {
      this.size += next.size
      this.next = next.next
      next.unlink()
      return this
    }
    return next
  }

  remove(job) {
    const { prev, next } = this
    if (prev === null && MemPartition.head === this) {
      MemPartition.head = next
    } else if (prev !== null) {
      prev.next = next
      if (next !== null) {
        next.prev = prev
      }
    }
    this.unlink()
    this.job = job
    this.state = MemPartition.stateType.BUSY
    return this
  }

  slice(size, job) {
    if (this.size > size) {
      const { address } = this
      this.size -= size
      this.address += size
      return new MemPartition({
        size,
        address,
        job,
        state: MemPartition.stateType.BUSY,
      })
    }
    return null
  }

  mergeInsert() {
    let last = null
    let cur = MemPartition.head
    this.state = MemPartition.stateType.FREE
    this.job = null
    while (cur && cur.address < this.address) {
      last = cur
      cur = cur.next
    }
    if (last === null) {
      if (MemPartition.head) {
        MemPartition.head.prev = this
      }
      this.next = MemPartition.head
      this.prev = null
      MemPartition.head = this
      this.merge()
    } else {
      if (cur) {
        cur.prev = this
      }
      this.next = cur
      this.prev = last
      last.next = this
      const n = last.merge()
      if (n) {
        n.merge()
      }
    }
  }
}

MemPartition.minsize = 1

MemPartition.stateType = {
  FREE: 0,
  BUSY: 1,
}

MemPartition.head = new MemPartition({
  size: 640,
})

module.exports = MemPartition
