///
/// \package astlib
/// \file benchmark.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13.4.2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///


var astlib = require('./build/Release/addon.node');
const ASTERIX = require('./asterixitems.js');

var asterixRecord = astlib.createAsterixRecord();
var codecs = astlib.enumerateAllCodecs();
var plot = astlib.createAsterixRecord();

astlib.setNumber(plot, ASTERIX.DSI_SAC, 44);
astlib.setNumber(plot, ASTERIX.DSI_SIC, 144);
astlib.setNumber(plot, ASTERIX.TIMEOFDAY, 3600);

astlib.setNumber(plot, ASTERIX.TRACK_DETECTION, 3);
astlib.setBoolean(plot, ASTERIX.TRACK_TEST, true);
astlib.setBoolean(plot, ASTERIX.TRACK_SIMULATED, true);

astlib.setNumber(plot, ASTERIX.TRACK_POSITION_RANGE, 10000.0);
astlib.setNumber(plot, ASTERIX.TRACK_POSITION_AZIMUTH, 45.0);

astlib.setBoolean(plot, ASTERIX.MODE3A_V, true);
astlib.setBoolean(plot, ASTERIX.MODE3A_G, true);
astlib.setBoolean(plot, ASTERIX.MODE3A_L, true);
astlib.setNumber(plot, ASTERIX.MODE3A_VALUE, 7777);

astlib.setNumber(plot, ASTERIX.TRACK_POSITION_X, -10000.0);
astlib.setNumber(plot, ASTERIX.TRACK_POSITION_Y, -50000.0);

astlib.setBoolean(plot, ASTERIX.MODE2_V, true);
astlib.setBoolean(plot, ASTERIX.MODE2_G, true);
astlib.setBoolean(plot, ASTERIX.MODE2_L, true);
astlib.setNumber(plot, ASTERIX.MODE2_VALUE, 7777);

astlib.setNumber(plot, ASTERIX.TRACK_NUMBER, 1111);
astlib.setString(plot, ASTERIX.AIRCRAFT_ADDRESS, '23FFAA');
astlib.setString(plot, ASTERIX.AIRCRAFT_IDENTIFICATION, 'PAKON321');
console.log(astlib.toString(plot));

var buffer = astlib.encodeAsterixRecord(plot, 'Eurocontrol-48:1.21');			
console.log(buffer);

for(var i = 0; i < 30000; i++) {
	var records = astlib.decodeAsterixBuffer('Eurocontrol-48:1.21', buffer);
	var record = records[0];
	astlib.setNumber(plot, ASTERIX.TIMEOFDAY, 3601);
	astlib.setBoolean(plot, ASTERIX.MODE2_V, true);
	astlib.setBoolean(plot, ASTERIX.MODE2_G, true);
	astlib.setBoolean(plot, ASTERIX.MODE2_L, true);
	astlib.setNumber(plot, ASTERIX.TRACK_DETECTION, 3);
	astlib.setBoolean(plot, ASTERIX.TRACK_TEST, true);
	astlib.setBoolean(plot, ASTERIX.TRACK_SIMULATED, true);
	astlib.setNumber(plot, ASTERIX.TRACK_POSITION_RANGE, 10000.0);
	astlib.setNumber(plot, ASTERIX.TRACK_POSITION_AZIMUTH, 45.0);	
	var buffer2 = astlib.encodeAsterixRecord(record, 'Eurocontrol-48:1.21');			
}

console.log(30000 / process.uptime());
