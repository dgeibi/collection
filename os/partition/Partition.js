const stateType = require('./stateType')
const { tlog } = require('../util')

class Partition {
  constructor(opts) {
    const options = Object.assign(
      {
        address: 0,
        size: 0,
        state: stateType.FREE,
        next: null,
        prev: null,
        job: null,
      },
      opts
    )
    const { address, size, next, prev, job, state } = options

    /** @type {number} */
    this.address = address

    /** @type {number} */
    this.size = size

    /** @type {Partition} */
    this.next = next

    /** @type {Partition} */
    this.prev = prev

    /** @type {number} */
    this.state = state

    this.job = job
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

  remove() {
    const { prev, next } = this
    if (prev === null && Partition.head === this) {
      Partition.head = next
    } else if (prev !== null) {
      prev.next = next
      if (next !== null) {
        next.prev = prev
      }
    }
    this.unlink()
    this.state = stateType.BUSY
    return this
  }

  slice(size) {
    if (this.size > size) {
      const { address } = this
      this.size -= size
      this.address += size
      return new Partition({
        size,
        address,
        state: stateType.BUSY,
      })
    }
    return null
  }

  mergeInsert() {
    let last = null
    let cur = Partition.head
    this.state = stateType.FREE
    while (cur && cur.address < this.address) {
      last = cur
      cur = cur.next
    }
    if (last === null) {
      if (Partition.head) {
        Partition.head.prev = this
      }
      this.next = Partition.head
      this.prev = null
      Partition.head = this
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

Partition.head = new Partition({
  size: 640,
})

Partition.minsize = 1

Partition.print = () => {
  let part = Partition.head
  const arr = []
  while (part) {
    arr.push(part)
    part = part.next
  }
  console.log('Free LinkedList:')
  tlog(arr)
}

module.exports = Partition
