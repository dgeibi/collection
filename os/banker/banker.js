const Res = require('./Res')

module.exports = banker

/**
 * 银行家算法
 * @param {number} i 作业索引
 * @param {number[]} reqs 资源请求数组
 * @param {Res[][]} alloc
 * @param {Res[][]} need
 * @param {Res[]} avail
 * @returns {number} 策略
 */
function banker({ i, reqs, alloc, need, avail }) {
  for (let j = 0; j < reqs.length; j += 1) {
    const req = reqs[j]
    if (req < 0) throw RangeError('req should be >= 0')
    // 请求的资源数超过宣布的最大值，忽略
    if (req > need[i][j].value) return banker.returnType.SKIP
    // 无足够资源，阻塞
    if (req > avail[j].value) return banker.returnType.BLOCK
  }
  // 复制操作
  const allocE = Res.cloneResssDeepI(alloc, i)
  const needE = Res.cloneResssDeepI(need, i)
  const availE = Res.cloneRess(avail)

  // 修改资源向量
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
 * 判断是否安全
 * @param {Res[][]} alloc
 * @param {Res[][]} need
 * @param {Res[]} avail
 */
function isSafe(alloc, need, avail) {
  const len = alloc.length
  const finishes = Array(len).fill(false)
  const work = Res.cloneRess(avail)
  for (let i = 0; i < len; i += 1) {
    // 找到可回收的资源并回收
    if (!finishes[i] && need[i].every((x, j) => x.value <= work[j].value)) {
      for (let j = 0; j < work.length; j += 1) {
        work[j].add(alloc[i][j])
      }
      finishes[i] = true

      // 外层循环重新开始
      i = -1
    }
  }
  // 所有作业均完成时返回 true
  return finishes.every(Boolean)
}
