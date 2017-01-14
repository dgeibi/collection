var http = require('http')
var url = require('url')

function parseTime(date) {
    return {
        hour: date.getHours(),
        minute: date.getMinutes(),
        second: date.getSeconds()
    }
}

function parseUnixTime(date) {
    return {
        "unixtime": date.getTime()
    }
}

var server = http.createServer((request, response) => {
    var iso = url.parse(request.url, true).query.iso
    var date = new Date(iso)
    var result
    if(request.url.startsWith('/api/unixtime')) {
        result = parseUnixTime(date)
    } else if (request.url.startsWith('/api/parsetime')) {
        result = parseTime(date)
    }

    if(result) {
        response.writeHead(200, { 'Content-Type': 'application/json' })
        response.end(JSON.stringify(result))
    } else {
        response.writeHead(404)
        response.end()
    }
})
server.listen(process.argv[2])