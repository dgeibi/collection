/**
 * @param {number|Res} t
 */
function valueOf(t) {
  let v = 0
  if (typeof t === 'number') {
    v = t
  } else if (typeof t === 'object' && t.value) {
    v = t.value
  }
  return v
}

class Res {
  constructor(name, value) {
    if (value < 0) throw Error('resource value should be >= 0')
    this.name = name
    /** @type {number} */
    this.value = value
  }

  /**
   * @param {number|Res} v
   */
  add(v) {
    if (v <= 0) return false
    const nv = valueOf(v) + this.value
    if (nv >= 0) {
      this.value = nv
      return true
    }
    return false
  }

  /**
   * @param {number|Res} v
   */
  reduce(v) {
    if (v <= 0) return false
    const nv = this.value - valueOf(v)
    if (nv >= 0) {
      this.value = nv
      return true
    }
    return false
  }

  /**
   * @param {Res} res
   * @param {number} value
   */
  share(res, value) {
    if (!(res instanceof Res)) throw TypeError('res should be a Res')
    if (typeof value !== 'number') throw TypeError('value should be a number')
    return this.reduce(value) && res.add(value)
  }

  clone() {
    return new Res(this.name, this.value)
  }

  static ress({ A = 0, B = 0, C = 0 } = {}) {
    return [new Res('A', A), new Res('B', B), new Res('C', C)]
  }

  /**
   * @param {Res[]} ress
   */
  static cloneRess(ress) {
    return ress.map(x => x.clone())
  }

  /**
   *
   * @param {Res[][]} resss
   * @param {number} i
   */
  static cloneResssDeepI(resss, i) {
    const nresss = resss.slice()
    nresss[i] = Res.cloneRess(resss[i])
    return nresss
  }

  /**
   * @param {Res[]} a
   * @param {number[]|Res[]} b
   */
  static reduces(a, b) {
    a.forEach((r, i) => {
      r.reduce(b[i])
    })
  }

  /**
   * @param {Res[]} a
   * @param {number[]|Res[]} b
   */
  static adds(a, b) {
    a.forEach((r, i) => {
      r.add(b[i])
    })
  }
}

module.exports = Res
