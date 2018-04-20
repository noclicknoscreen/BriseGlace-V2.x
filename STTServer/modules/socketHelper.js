
// ===========================================================================
// Socket Helper : IP Decoder, Player number management
// ===========================================================================

module.exports = {

  decodeIp: function(socket){
    var ipAddr = socket.handshake.address;

    if (ipAddr.substr(0, 7) == "::ffff:") {
      ipAddr = ipAddr.substr(7)
    }
    return ipAddr;

  },

  playerNr: function(socket){

    var nr;
    var ip = this.decodeIp(socket);

    switch (ip) {
      case '192.168.1.102':
      nr = 1;
      break;
      case '192.168.1.103':
      nr = 2;
      break;
      default:
      nr = 0;
      break;

    }

    return nr;

  }


};
