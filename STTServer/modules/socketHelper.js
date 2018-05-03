
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
      case '192.168.2.21':
      nr = 1;
      break;
      case '192.168.2.22':
      nr = 2;
      break;
      case '192.168.2.23':
      nr = 3;
      break;
      default:
      nr = 0;
      break;

    }

    return nr;

  }


};
