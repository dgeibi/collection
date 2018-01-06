function pick(obj, keys, fn) {
  const data = {}
  for (let i = 0; i < keys.length; i++) {
    const key = keys[i];
    fn({
      data,
      value: obj[key],
      key,
      index: i,
    })
  }
  return data
}

export default pick
