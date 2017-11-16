exports.getRandomInt = function getRandomInt(from, to) {
  const min = Math.ceil(from)
  return Math.floor(Math.random() * (Math.floor(to) - min)) + min
}

exports.repeat = function repeat(time, fn) {
  let cnt = 0
  const rets = []
  while (cnt < time) {
    rets.push(fn())
    cnt += 1
  }
  return rets
}

const TCharts = require('tcharts.js')

const { Table } = TCharts
const table = new Table(0.2)

exports.tlog = function tlogObjs(datas) {
  const first = datas[0]
  if (!first) {
    return console.log('nothing')
  }
  if (Array.isArray(first)) {
    table.setData(datas)
    return console.log(table.string())
  }
  const keys = Object.keys(first)
  const valuess = datas.map(d => Object.values(d))
  table.setData([keys, ...valuess])
  return console.log(table.string())
}
