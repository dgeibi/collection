module.exports = function makeJobMatchSnapshot(tap, getTime) {
  return function matchSnapshot(x) {
    const time = getTime()
    tap.matchSnapshot(x.arrived, `arrived | T${time}`)
    tap.matchSnapshot(x.dead, `dead | T${time}`)
  }
}
