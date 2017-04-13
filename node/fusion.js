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
const astlib = require('./build/Release/addon.node');
const ASTERIX = require('./asterixitems.js');
const codecs = astlib.enumerateAllCodecs();

console.log(codecs);

server.on('error', (err) => {
	  console.log(`server error:\n${err.stack}`);
	  server.close();
	});

server.on('message', (msg, rinfo) => {
  console.log(`server got: ${msg} from ${rinfo.address}:${rinfo.port}`);
  var records = astlib.decodeAsterixBuffer('Eurocontrol-48:1.21', msg);
  for(var record in records) {
  //var record = records[0];
	if (record == null)
		continue;
  	console.log(astlib.toString(record));
  
  	astlib.setNumber(record, ASTERIX.TRACK_NUMBER, 1111);
  
  	var buffer2 = astlib.encodeAsterixRecord(record, 'Eurocontrol-62:1.16');
  
  	client.send(buffer2, 50001, 'localhost', (err) => { client.close(); });
  }
});

server.on('listening', () => {
  var address = server.address();
  console.log(`server listening ${address.address}:${address.port}`);
});

server.bind(50000);

/*
for(var i = 0; i < 30000; i++) {
	var records = astlib.decodeAsterixBuffer('Eurocontrol-48:1.21', buffer);
	var record = records[0];
	var buffer2 = astlib.encodeAsterixRecord(record, 'Eurocontrol-48:1.21');			
}

*/