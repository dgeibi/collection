var http = require('http');
(function dosomething(urls, start, end) {
    if(start < end) {
        http.get(urls[start], response => {
            var data = ""
            response.setEncoding('utf8')
            response.on('error', console.error)
            response.on('data', chunk=>{
                data += chunk
            })
            response.on('end', () => {
                console.log(data)
                dosomething(urls, start + 1, end)
            })
        }).on('error', console.error)
    }
})(process.argv, 2, 5)