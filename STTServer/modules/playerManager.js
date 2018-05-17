// API socket to json

var socketHelper = require('./socketHelper');

var players = [];
var lastMessage = {time:new Date().toLocaleString(), text:"", textToCompare:""};
var lastNumber = 0;

module.exports = {
  // Reset all players, empty datas

  // Add a player when connecting
  addPlayer: function (socket){

    var myIpAddr = socketHelper.decodeIp(socket);
    var myNumber = socketHelper.playerNr(socket);
    if(myNumber <= 0){
      console.log('IP undefined ('+myIpAddr+'): no player added');
      return null;
    }
    var foundPlayer = findPlayerByIp(myIpAddr);

    if (foundPlayer === undefined) {

      console.log("New player +++++++++++++++++++");

      // Set the player
      var newPlayer = {
        ip:myIpAddr,
        nr:myNumber,
        socketId:socket.id,
        isAvailable:true,
        lastMessage:lastMessage,
        volume:0
        // History of messages are now useless
        //messages:[]
      };
      // Make it available
      setTimeout(function(){ newPlayer.isAvailable = false; }, 20000);
      // Add it
      players.push(newPlayer);
      return newPlayer;

    } else {

      console.log("Old player found =============");

      foundPlayer.ip = myIpAddr;
      foundPlayer.nr = myNumber;
      foundPlayer.socketId = socket.id;
      // foundPlayer.isAvailable = false;
      // foundPlayer.lastMessage = "";
      // foundPlayer.messages = [];
      return foundPlayer;

    }


  },

  strPlayers: function(){
    var thosePlayers = {lastMessage:lastMessage, lastNumber:lastNumber, players:players};
    return thosePlayers;
  },

  // Add messsage to the player
  // inputs :
  // (int) Player number to select (or socketId)
  // (String) message
  addMessage: function (socket, message){

    // Check if existing playerNr / socketId
    var myIpAddr = socketHelper.decodeIp(socket);
    var foundPlayer = findPlayerByIp(myIpAddr);

    if (foundPlayer != undefined) {
        console.log("Old player found, Id:" + socket.id + " IP:" + myIpAddr);

        lastMessage = {time:new Date().toLocaleString(), text:message, textToCompare:suppressAccents(message)};
        lastNumber = foundPlayer.nr;
        // Add message to the list (nope, we don't send all message any more
        //foundPlayer.messages.push(lastMessage);
        // Change last message
        foundPlayer.lastMessage = lastMessage;
        // Make it available
        foundPlayer.isAvailable = true;
    }
    return foundPlayer;
  },

  // Update the volume of the player
  // inputs :
  // (Socket) Identified socket
  // (Float) Volume value
  updateVolume: function (socket, volume){

    // Check if existing playerNr / socketId
    var myIpAddr = socketHelper.decodeIp(socket);
    var foundPlayer = findPlayerByIp(myIpAddr);

    if (foundPlayer != undefined) {
        //console.log("Old player found =============");
        // Add message to the list
        foundPlayer.volume = volume;
    }
    return foundPlayer;
  },

  // Reset players (basically, last messages)
  resetPlayers: function (){

      lastMessage = {time:new Date().toLocaleString(), text:""};

      for (var idxPlayer in players) {
        players[idxPlayer].lastMessage = {time:new Date().toLocaleString(), text:""};
      }

  }

};

function findPlayerByIp(existingIp){

  var foundPlayer = players.find(function (foundPlayer) {
      //console.log(existingIp);
      return foundPlayer.ip === existingIp;
   });

  return foundPlayer;

}

function suppressAccents(word){

  word = word.toString();

  word=word.replace("á","a");
  word=word.replace("â","a");
  word=word.replace("Á","A");

  word=word.replace("ç","c");

  word=word.replace("é","e");
  word=word.replace("è","e");
  word=word.replace("ê","e");
  word=word.replace("É","E");

  word=word.replace("í","i");
  word=word.replace("Í","I");
  word=word.replace("î","i");

  word=word.replace("ó","o");
  word=word.replace("Ó","O");
  word=word.replace("ô","o");

  word=word.replace("œ","oe");

  word=word.replace("ú","u");
  word=word.replace("Ú","U");
  word=word.replace("û","U");

  word=word.replace("ñ","n");
  word=word.replace("Ñ","N");

  word=word.toLowerCase();

  return word;

}
