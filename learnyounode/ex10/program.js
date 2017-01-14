var net = require('net')
function pad (i) {
    return (i < 10 ? '0' : '') + i
}
var server = net.createServer(function (socket) {  
    var date = new Date();
    var year = date.getFullYear()
    var month = pad(date.getMonth() + 1)
    var day = pad(date.getDate())
    var minute = pad(date.getMinutes())
    var hour = pad(date.getHours());
    var time = `${year}-${month}-${day} ${hour}:${minute}\n`
    socket.end(time);
})
server.listen(+process.argv[2])