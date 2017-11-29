/* eslint-disable no-param-reassign, no-mixed-operators */
// copy from http://blog.csdn.net/ljianhui/article/details/13761901
gameSchedule(8)

function gameSchedule(number) {
  const table = Array(number * number).fill(0)
  for (let i = 0; i < number; i += 1) {
    table[i * number] = i + 1
  }
  schedule(table, number, number, 0, 0, number - 1, number - 1)
  print(table, number)
}

function print(table, rank) {
  for (let i = 0; i < rank; i += 1) {
    const o = i * rank
    console.log(table.slice(o, o + rank).join(' '))
  }
}

function schedule(table, rank, n, r1, c1, r2, c2) {
  if (n < 2) return
  for (let i = 0; i < n; i += 1) {
    if (table[rank * (r1 + i) + c1] !== 0) {
      table[rank * (r2 - i) + c2] = table[rank * (r1 + i) + c1]
    } else {
      table[rank * (r1 + i) + c1] = table[rank * (r2 - i) + c2]
    }
  }
  const dr = Math.floor((r2 - r1) / 2)
  const dc = Math.floor((c2 - c1) / 2)
  n /= 2
  const r3 = r1 + dr
  const c3 = c1 + dc
  const r4 = r3 + 1
  const c4 = c3 + 1
  schedule(table, rank, n, r1, c1, r3, c3)
  schedule(table, rank, n, r1, c4, r3, c2)
  schedule(table, rank, n, r4, c1, r2, c3)
  schedule(table, rank, n, r4, c4, r2, c2)
}
