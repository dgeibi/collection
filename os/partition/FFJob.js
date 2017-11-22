const Partition = require('./Partition')
const { tlog } = require('../util')

class FFJob {
  constructor(num) {
    this.name = `Job${num}`

    /** @type {Partition[]} */
    this.partitions = []
  }

  alloc(part, size) {
    if (part.size - size <= Partition.minsize) {
      this.partitions.push(part.remove())
    } else {
      this.partitions.push(part.slice(size))
    }
  }

  request(size) {
    let part = Partition.head
    let ret = false
    while (part !== null && ret === false) {
      if (part.size > size) {
        this.alloc(part, size)
        ret = true
      } else {
        part = part.next
      }
    }
    this.print(ret, size)
    return ret
  }

  release(size) {
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
    this.print(ret, size, true)
    return ret
  }

  print(ret, size, release = false) {
    const action = release ? 'release' : 'request'
    if (ret) {
      console.log(`${this.name} ${action} ${size} KB: OK`)
      console.log(`${this.name} partitions:`)
      tlog(this.partitions)
      Partition.print()
    } else {
      console.log(`${this.name} ${action} ${size} KB: FAIL`)
    }
  }
}

module.exports = FFJob
