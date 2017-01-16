var http = require('http')
var map = require('through2-map')

var server = http.createServer((request, response) => {
    if (request.method !== 'POST') {
        return response.end('send me a POST\n')
    }
    request.pipe(map(chunk => chunk.toString().toUpperCase())).pipe(response)
})

server.listen(process.argv[2])