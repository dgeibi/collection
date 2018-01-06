exports.maybeUndefined = (value, fallback) =>
  value === undefined ? (typeof fallback === 'function' ? fallback() : fallback) : value

exports.repeat = function repeat(time, fn) {
  let cnt = 0
  const rets = []
  while (cnt < time) {
    rets.push(fn())
    cnt += 1
  }
  return rets
}
