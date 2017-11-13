const THRESHOLD = 1e3
const INIT_OFFSET = 1
const INIT_CURRENT = 0
function catchRabbit(number) {
  const viewed = new Array(number)
  let current = INIT_CURRENT
  let offset = INIT_OFFSET
  let count = 0
  do {
    count += 1
    viewed[current] = true
    offset = (offset + 1) % number
    current = (current + offset) % number
  } while (count < THRESHOLD && !(current === INIT_CURRENT && offset === INIT_OFFSET))
  const notViewed = []
  for (let i = 0; i < viewed.length; i += 1) {
    if (!viewed[i]) notViewed.push(i + 1)
  }
  return notViewed
}

module.exports = catchRabbit
