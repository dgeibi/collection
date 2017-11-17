const Res = require('./Res')

module.exports = banker

/**
 *
 * @param {number} i
 * @param {number[]} reqs
 * @param {Res[][]} alloc
 * @param {Res[][]} need
 * @param {Res[]} avail
 */
function banker({ i, reqs, alloc, need, avail }) {
  for (let j = 0; j < reqs.length; j += 1) {
    const req = reqs[j]
    if (req < 0) throw RangeError('req should be >= 0')
    if (req > need[i][j].value) return banker.returnType.SKIP
    if (req > avail[j].value) return banker.returnType.BLOCK
  }
  const allocE = Res.cloneResssDeepI(alloc, i)
  const needE = Res.cloneResssDeepI(need, i)
  const availE = Res.cloneRess(avail)

  for (let j = 0; j < reqs.length; j += 1) {
    const req = reqs[j]
    availE[j].reduce(req)
    allocE[i][j].add(req)
    needE[i][j].reduce(req)
  }
  return isSafe(allocE, needE, availE) ? banker.returnType.OK : banker.returnType.SKIP
}

banker.returnType = {
  BLOCK: 0,
  SKIP: 1,
  OK: 2,
}

/**
 * @param {Res[][]} alloc
 * @param {Res[][]} need
 * @param {Res[]} avail
 */
function isSafe(alloc, need, avail) {
  const len = alloc.length
  const finishes = Array(len).fill(false)
  const work = Res.cloneRess(avail)
  for (let i = 0; i < len; i += 1) {
    if (!finishes[i] && need[i].every((x, j) => x.value <= work[j].value)) {
      for (let j = 0; j < work.length; j += 1) {
        work[j].add(alloc[i][j])
      }
      finishes[i] = true
      i = -1
    }
  }
  return finishes.every(Boolean)
}
