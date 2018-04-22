var messages  = [];
var myIp = "";
var myPlayerName = "";

var SpeechRecognition = window.webkitSpeechRecognition;
var recognition = new SpeechRecognition();
recognition.lang = "fr-FR";
recognition.continuous = true;

recognition.onstart = function() {
  console.log("Started recognition");
}

recognition.onerror = function(event) {
  console.log("Error : ");
  console.log(event);
}

recognition.onend = function() {
  console.log("Stopped recognition");
  recognition.start();
}

recognition.onresult = function(event) {

  console.log("Result append !")

  if(event.results && event.results.length > 0 ) {

    var transcript = event.results[event.results.length-1][0].transcript;
    console.log(event.results);
    updateList(transcript);
    sendWords(transcript);
  }else{
    console.log("No available results");
  }

}

// recognition.start();

function updateList(message) {
  var txt = "";
  var ul = document.getElementById("messagesList");
  ul.innerHTML = "";

  messages.push((new Date).toLocaleString() + " : " + message);

  for( var i = messages.length - 1; i >=0; i--) {
    var li=document.createElement('li');
    li.innerHTML = messages[i];
    ul.appendChild(li);
  }

}
function updateMyIp(ip){
  myIp = ip;
  document.getElementById("myIp").innerHTML = "my IP is " + myIp;
}
function updateMyPlayerName(nr){
  myPlayerNr = nr;
  document.getElementById("myPlayerNr").innerHTML = "my name is player " + myPlayerNr;
}


// ===========================================================
// Socket section
// ===========================================================
var socketClient = io({
  reconnection: true,
  reconnectionDelay: 1000,
  reconnectionDelayMax : 5000,
  reconnectionAttempts: Infinity
});

// var tryReconnect = function(){
//
//     if (socketClient.connected === false &&
//         socketClient.connecting === false) {
//         // use a connect() or reconnect() here if you want
//         console.log('Try to reconnect !')
//         socketClient.connect()
//    }
// }
//
// var intervalID = setInterval(tryReconnect, 2000);

socketClient.on('connect', () => {
  recognition.start();
});

socketClient.on('disconnect', () => {
  console.log('Disconnected ====> Re-Open');
  socketClient.open();
  recognition.stop();
});

socketClient.on('myPlayer', (datas) => {
  console.log('Player received : ')
  console.log(datas);

  updateMyIp(datas.ip);
  updateMyPlayerName(datas.nr);

});

function sendWords(words){
  console.log('sending words to server : ' + words);
  socketClient.emit('words', words);
}

// set interval for weird bug
// this will stop the recognition, onend event is shot, then recognition is back again
// ¯\_(ツ)_/¯
setInterval(resetVoiceRecog, 10000);
function resetVoiceRecog() {
  recognition.stop();
}

function forceSend(){
    sendWords(document.getElementById("wordToSend").value);
}
function forceSendRnd(){
    var rndString = Math.random().toString(36).substring(2, 15) + Math.random().toString(36).substring(2, 15);
    sendWords(rndString);
}
