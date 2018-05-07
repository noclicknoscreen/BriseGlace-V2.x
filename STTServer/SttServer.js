

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
var ioServer = require('socket.io')
var io = new ioServer();
io.attach(httpServer);
io.attach(httpsServer);

// Home made modules -----------------------------------
var playerManager = require('./modules/playerManager');
var socketHelper = require('./modules/socketHelper');


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
app.get('/players', function(req, res) {

  //console.log("Players sent to HTTP : ");

  res.setHeader('Content-Type', 'application/json');
  res.send(JSON.stringify(playerManager.strPlayers()));
});

const options = {
  key: fs.readFileSync(__dirname + '/public/certificates/key.pem'),
  cert: fs.readFileSync(__dirname + '/public/certificates/cert.pem'),
  passphrase: '@@kons3n',
};

// --------------------------------------------
// Socket section

var socketServer = io.on('connection', (socket) => {

  console.log('recognition connected : ' + socket.id);
  // Add player
  var player = playerManager.addPlayer(socket);

  if(player != null){
    // Send to client who he is
    sendPlayerToRecognition(socket, player);

    // Send all players to Display
    sendPlayersToDisplay(socket);

    // Get the words speech detected
    socket.on('words', (data) => {
      // Nouveau message
      var foundPlayer = playerManager.addMessage(socket, data);
      console.log("New message from " + foundPlayer.nr + ":" + foundPlayer.ip);
      console.log(data);
      // Wait for availability to go down
      setTimeout(function(){
        foundPlayer.isAvailable = false;
        sendPlayersToDisplay(socket);
      }, 5000);
      // Send all players to Display
      sendPlayersToDisplay(socket);
    });

    // Get the words speech detected
    socket.on('volume', (volume) => {
        //console.log('Volume informations from player n°' + nr + " : " + volume);
        playerManager.updateVolume(socket, volume);
    });

  }

});

function sendPlayersToDisplay(socket) {
  // Send all players
  console.log("Players sent to display : ");
  //console.log(playerManager.strPlayers());
  socket.broadcast.emit('players', playerManager.strPlayers());
  // displaySocket.emit('players', playerManager.players());
}

function sendPlayerToRecognition(socket, player){
  // Send to client who he is
  console.log("Player sent to recognition : ");
  //console.log(player);
  socket.emit('myPlayer', player);
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
