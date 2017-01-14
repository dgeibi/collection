var http = require('http')
var fs = require('fs')

var port = process.argv[2], file = process.argv[3]
var server = http.createServer((request, response) => {
    response.writeHead(200, { 'Content-Type': 'text/plain' })
    fs.createReadStream(file).pipe(response)
})

server.listen(port)