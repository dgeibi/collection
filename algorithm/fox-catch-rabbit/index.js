const assert = require('assert')
const catchRabbit = require('./catchRabbit')

assert.deepStrictEqual(catchRabbit(13), [4, 5, 7, 9, 11, 12])
assert.deepStrictEqual(catchRabbit(10), [2, 4, 7, 9])
