// API socket to json

var socketHelper = require('./socketHelper');

var players = [];

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
        lastMessage:"",
        messages:[]
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
    var thosePlayers = {players:players};
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
        console.log("Old player found =============");
        var newMessage = {time:new Date().toLocaleString(), text:message};
        // Add message to the list
        foundPlayer.messages.push(newMessage);
        // Change last message
        foundPlayer.lastMessage = message;
        // Make it available
        foundPlayer.isAvailable = true;
    }
    return foundPlayer;
  }

};

function findPlayerByIp(existingIp){

  var foundPlayer = players.find(function (foundPlayer) {
      console.log(existingIp);
      return foundPlayer.ip === existingIp;
   });

  return foundPlayer;

}
