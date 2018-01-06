const { maybeUndefined } = require('./util')

class MemPartition {
  constructor({ address, size, next, prev, job, state, holder } = {}) {
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

    this.holder = maybeUndefined(holder, () => MemPartition)
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
      if (this.next) {
        this.next.prev = this
      }
      next.unlink()
      return this
    }
    return null
  }

  remove(job) {
    const { prev, next } = this
    if (prev === null && this.holder.memory === this) {
      this.holder.memory = next
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
        holder: this.holder,
      })
    }
    return null
  }

  mergeInsert() {
    let last = null
    let cur = this.holder.memory
    this.state = MemPartition.stateType.FREE
    this.job = null
    while (cur && cur.address < this.address) {
      last = cur
      cur = cur.next
    }
    if (last === null) {
      if (this.holder.memory) {
        this.holder.memory.prev = this
      }
      this.next = this.holder.memory
      this.prev = null
      this.holder.memory = this
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

MemPartition.memory = new MemPartition({
  size: 640,
})

module.exports = MemPartition
