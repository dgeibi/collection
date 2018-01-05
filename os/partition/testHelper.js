const Partition = require('./Partition')

module.exports = Job => {
  const jobs = Array(8)
    .fill(null)
    .map((v, i) => new Job(i + 1))

  function t(i) {
    return jobs[i - 1]
  }

  Partition.print()
  t(1).request(130)
  t(2).request(60)
  t(3).request(100)
  t(2).release(60)
  t(4).request(200)
  t(3).release(100)
  t(1).release(130)
  t(5).request(140)
  t(6).request(60)
  t(7).request(50)
  t(8).request(60)
}
