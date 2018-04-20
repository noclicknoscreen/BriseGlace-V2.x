// API socket to json

var socketHelper = require('./socketHelper');

var players = [];

module.exports = {
  // Reset all players, empty datas

  // Add a player when connecting
  addPlayer: function (socket){

    var myIpAddr = socketHelper.decodeIp(socket);
    var myNumber = socketHelper.playerNr(socket);
    var foundPlayer = findPlayerByIp(myIpAddr);

    if (foundPlayer === undefined) {

      console.log("New player +++++++++++++++++++");

      // Set the player
      var newPlayer = {
        ip:myIpAddr,
        nr:myNumber,
        socketId:socket.id,
        isAvailable:false,
        lastMessage:"",
        messages:[]
      };

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

  players: function(){
    return players;
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
        console.log("Old player found =============");
        var newMessage = {time:new Date().toLocaleString(), text:message};
        // Add message to the list
        foundPlayer.messages.push(newMessage);
        // Change last message
        foundPlayer.lastMessage = message;
    }

  }

};

function findPlayerByIp(existingIp){

  var foundPlayer = players.find(function (foundPlayer) {
      console.log(existingIp);
      return foundPlayer.ip === existingIp;
   });

  return foundPlayer;

}
