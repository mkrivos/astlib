///
/// \package astlib
/// \file fusion.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13.4.2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

const dgram = require('dgram');
const server = dgram.createSocket('udp4');
const client = dgram.createSocket('udp4');

server.on('error', (err) => {
	  console.log(`server error:\n${err.stack}`);
	  server.close();
	});

server.on('message', (msg, rinfo) => {
  console.log(`server got: ${msg.toString()} from ${rinfo.address}:${rinfo.port}`);
  var records = astlib.decodeAsterixBuffer('Eurocontrol-48:1.21', msg);
  var record = records[0];
});

server.on('listening', () => {
  var address = server.address();
  console.log(`server listening ${address.address}:${address.port}`);
});

server.bind(50001);
