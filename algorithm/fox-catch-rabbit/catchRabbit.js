function catchRabbit(number) {
  const viewed = new Array(number)
  let current = 0
  let offset = 1
  let count = 0
  while (count < number) {
    count += 1
    viewed[current] = true
    offset = (offset + 1) % number
    current = (current + offset) % number
  }
  const notViewed = []
  for (let i = 0; i < viewed.length; i += 1) {
    if (!viewed[i]) notViewed.push(i + 1)
  }
  return notViewed
}

module.exports = catchRabbit
