var http = require('http')
http.get(process.argv[2], response => {
    var data = ""
    response.setEncoding('utf8')
    response.on('error', console.error)
    response.on('data', chunk => {
        data += chunk
    })
    response.on('end', ()=>{
        console.log(data.length)
        console.log(data)
    })
}).on('error', console.error)