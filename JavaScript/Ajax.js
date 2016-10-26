/* Cross Browser CORS Requset */
/* Professional JavaScript for Web Developers 3rd */

function createCORSRequest(method, url) {
    var xhr = new XMLHttpRequest();
    if( "withCredentials" in xhr ) {
        xhr.open(method, url, true);
    } else if (typeof XDomainRequest != "undefined") {
        xhr = new XDomainRequest(); /* Internet Explorer 8 and 9 */
        xhr.open(method, url);
    }
    return xhr;
}

/* Usage */
var request = createCORSRequest("get", "http://www.somewhere-else.com/page/");
if (request) {
    request.onload = function() {
        /* do something */
        alert(request.responseText);
    };
    request.onerror = function() {
        console.error("Request: an error occurred.");
    };
    request.send();
}
