var fs = require('fs');

var privateKey  = fs.readFileSync(__dirname + '/public/certificates/key.pem');
var certificate = fs.readFileSync(__dirname + '/public/certificates/cert.pem');

var credentials = {key: privateKey, cert: certificate, passphrase: '@@kons3n'};
var express = require('express');
var app = express();

// your express configuration here
var httpServer = require('http').createServer(app);
var httpsServer = require('https').createServer(credentials, app);

//var http = require('http').Server(app);
var ioHttp = require('socket.io')(httpServer);
var ioHttps = require('socket.io')(httpsServer);

httpServer.listen(8080, function(){
  console.log('listening http STT Server on port 8080');
  console.log('--');
});

httpsServer.listen(8443, function(){
  console.log('listening https STT Server on port 8443');
  console.log('--');
});

var userId = 0;

ioHttp.on('connection', (socket) => {

  socket.userId = userId ++;
  console.log('a user connected, user id: ' + socket.userId);

  socket.on('chat', function(msg){
    console.log('message from user#' + socket.userId + ": " + msg);
    io.emit('chat', {
      id: socket.userId,
      msg: msg
    });
  });

  setInterval(function() {
    console.log('HeartBeat !!');
    socket.emit('heartbeat', 'tcha tcha tcha');
  }, 10000);

});
