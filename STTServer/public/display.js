var messagesToDisplay = [];
var socketClient = io('/display', {
  reconnection: true,
  reconnectionDelay: 1000,
  reconnectionDelayMax : 5000,
  reconnectionAttempts: Infinity
});

socketClient.on('disconnect', () => {
  console.log('Disconnected ====> Re-Open');
  socketClient.connect();
});

socketClient.on('wordsToDisplay', (sender, words) => {
  // send a private message to the socket with the given id
  console.log("New words to display  from player " + sender + "=[" + words + "]");
  updateList(sender, words);

});

function updateList(sender, message) {
  var txt = "";
  var ul = document.getElementById("messagesList" + sender);
  var li=document.createElement('li');

  li.innerHTML = (new Date).toLocaleString() + " : " + sender + " : " + message;
  ul.appendChild(li);

  // Waiting for correct bidimentionnal messages, or dictionnary instead of array
  // ul.innerHTML = "";
  //
  // messagesToDisplay.push((new Date).toLocaleString() + " : " + sender + " : " + message);
  //
  // for( var i = messagesToDisplay.length - 1; i >=0; i--) {
  //   var li=document.createElement('li');
  //   li.innerHTML = messagesToDisplay[i];
  //   ul.appendChild(li);
  // }

}
