#!/usr/bin/env node
var fs = require('fs');
var ext = '.' + process.argv[3];
fs.readdir(process.argv[2], function(err, files){
    if(err) throw(err);
    files.filter(function(file){
        return file.endsWith(ext);
    }).forEach(function(file) {
        console.log(file);
    });
});