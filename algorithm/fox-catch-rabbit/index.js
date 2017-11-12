const assert = require('assert')
const catchRabbit = require('./catchRabbit')

assert.deepStrictEqual(catchRabbit(10), [2, 4, 7, 9])
