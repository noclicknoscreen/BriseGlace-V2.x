var messagesToDisplay = [];
var socketClient = io({
  reconnection: true,
  reconnectionDelay: 1000,
  reconnectionDelayMax : 5000,
  reconnectionAttempts: Infinity
});

socketClient.on('disconnect', () => {
  console.log('Disconnected ====> Re-Open');
  socketClient.connect();
});

socketClient.on('players', (datas) => {

  // Get the div for all players
  var divPlayers = document.getElementById("players");
  divPlayers.innerHTML = "";

  // send a private message to the socket with the given id
  // console.log("Players received :");
  // console.log(datas);

  for (var indx in datas) {
    addPlayer(datas[indx], datas.length, divPlayers);
  }

});

// -------------------------------------------------------
// Add a player
// --------------------------------------------------------
function addPlayer(player, nbPlayers, divPlayers){

  var playerDiv = document.createElement('div');
  playerDiv.classList.add("player");
  playerDiv.style.width = (95 / nbPlayers) + "%";

  console.log("Add player");
  console.log(player);

  // ---------------------------------------------------------------------
  // Display IP of each player
  if (player.hasOwnProperty('ip')) {
    var p = document.createElement('p');
    var t = document.createTextNode("ip : " + player.ip);     // Create a text node
    p.appendChild(t);
    playerDiv.appendChild(p);
  }

  // ---------------------------------------------------------------------
  // Display number of each player
  if (player.hasOwnProperty('nr')) {
    // One Title : Player number
    var p = document.createElement('p');
    var t = document.createTextNode("nr : " + player.nr);     // Create a text node
    p.appendChild(t);
    playerDiv.appendChild(p);
  }

  // ---------------------------------------------------------------------
  // Display whole message
  if (player.hasOwnProperty('messages')) {
    var ul = document.createElement('ul');
    for(var indx in player.messages){
        var li = document.createElement('li');
        playerDiv.classList.add("message");
        li.innerHTML = player.messages[indx].time + " : " + player.messages[indx].text;
        ul.appendChild(li);
    }
    playerDiv.appendChild(ul);
  }

  // add whole bunch ------------------------------------------
  divPlayers.appendChild(playerDiv);

}
