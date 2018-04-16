

var fs = require('fs');
var http = require('http');
var https = require('https');
var privateKey  = fs.readFileSync(__dirname + '/public/certificates/key.pem');
var certificate = fs.readFileSync(__dirname + '/public/certificates/cert.pem');

var credentials = {key: privateKey, cert: certificate, passphrase: '@@kons3n'};
var express = require('express');
var app = express();

// your express configuration here

var httpServer = http.createServer(app);
var httpsServer = https.createServer(credentials, app);

//var http = require('http').Server(app);
var io = require('socket.io')(httpsServer);

httpServer.listen(8080, function(){
  console.log('listening http STT Server on port 8080');
  console.log('--');
});

httpsServer.listen(8443, function(){
  console.log('listening https STT Server on port 8443');
  console.log('--');
});


console.log('==================================================');
console.log();
console.log('Server starting at : ' + (new Date().toLocaleString()));
console.log();
console.log('Server Notes :');
console.log('Recognition page : /recognition');
console.log('Display page : /display');
console.log('--');

app.use('/public', express.static(__dirname + '/public'));

app.get('/recognition', function(req, res) {
  res.sendFile(__dirname + '/public/recognition.html');
});
app.get('/display', function(req, res) {
  res.sendFile(__dirname + '/public/display.html');
});

const options = {
  key: fs.readFileSync(__dirname + '/public/certificates/key.pem'),
  cert: fs.readFileSync(__dirname + '/public/certificates/cert.pem'),
  passphrase: '@@kons3n',
};

// --------------------------------------------
// Socket section
var nspReco = io.of('/recognition');
nspReco.on('connection', (socket) => {

  console.log('recognition connected : ' + socket.id);
  var ipAddr = decodeIp(socket);
  socket.emit('myIpMyName', {ip:ipAddr, nr:givePlayerNumber(ipAddr)});

  socket.on('words', (data) => {

    var ipAddr = decodeIp(socket);
    var playerNr = givePlayerNumber(ipAddr);

    // send a private message to the socket with the given id
    console.log("New words from player " + playerNr + " : " + data);
    nspDisplay.emit('wordsToDisplay', playerNr, data);

  });

});

var nspDisplay = io.of('/display');
nspDisplay.on('connection', (socket) => {
  console.log('display connected : ' + socket.id);
});

function decodeIp(socket){

  var ipAddr = socket.handshake.address;

  if (ipAddr.substr(0, 7) == "::ffff:") {
    ipAddr = ipAddr.substr(7)
  }
  console.log('New connection from ' + socket.id + " : " + ipAddr);

  return ipAddr;

}

function givePlayerNumber(ip){

  var playerNr;

  switch (ip) {
    case '192.168.1.102':
    playerNr = 1;
    break;
    case '192.168.1.103':
    playerNr = 2;
    break;
    default:
    playerNr = 0;
    break;

  }

  console.log('Giving player number : [Number]=' + playerNr + '; [IP]=' + ip);
  return playerNr;

}


// mySocket.on('connection', (socket) => {
//
//   console.log("New socket connection: " + socket.id);
//
//   socket.on('words', (data) => {
//     // send a private message to the socket with the given id
//     console.log("New words from " + socket.id + " : ");
//     console.log(data);
//   });
//
// });
