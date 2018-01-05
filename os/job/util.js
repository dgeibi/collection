exports.maybeUndefined = (value, fallback) =>
  value === undefined ? (typeof fallback === 'function' ? fallback() : fallback) : value

exports.getSnapshot = instance => {
  const data = {}
  const keys = Object.keys(instance)
  for (let i = 0; i < keys.length; i++) {
    const key = keys[i]
    let value = instance[key]
    if ((value && typeof value === 'object') || typeof value === 'function') {
      value = String(value)
    }
    data[key] = value
  }
  return data
}
