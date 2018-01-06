export const isPositiveNumber = (rule, value, callback) => {
  const n = Number(value)
  if (Number.isNaN(n) || n <= 0) {
    return callback('需要一个正数')
  }
  return callback()
}

export const isPostiveInteger = (rule, value, callback) => {
  const n = Number(value)
  if (Number.isInteger(n) && n > 0) {
    return callback()
  }
  return callback('需要一个正整数')
}

