//
// Copyright (c) 2013-2016 Pavel Medvedev. All rights reserved.
//
// This file is part of v8pp (https://github.com/pmed/v8pp) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

var assert = require("assert");
var astlib = require('./build/Release/addon.node');
const ASTERIX = require('./asterixitems.js');

var asterixRecord = astlib.createAsterixRecord();
var codecs = astlib.enumerateAllCodecs();

describe('AsterixRecord', function() {
	describe('#create', function() {
		it('"assert exists', function() {
			assert.ok(asterixRecord != null);			
		});
	}); 	

	describe('#set/get', function() {
		it('Real Number', function() {
			var pi = 3.14;
			assert(astlib.hasItem(asterixRecord, ASTERIX.TRACK_POSITION_LATITUDE) == false);
			astlib.setNumber(asterixRecord, ASTERIX.TRACK_POSITION_LATITUDE, pi);
			assert(astlib.hasItem(asterixRecord, ASTERIX.TRACK_POSITION_LATITUDE) == true);	
			assert(astlib.getNumber(asterixRecord, ASTERIX.TRACK_POSITION_LATITUDE) == pi);
		});

		it('Real Number Array', function() {
			var pi2 = [ 3.14, 6.28 ];
			assert(astlib.hasItem(asterixRecord, ASTERIX.AICRAFT_DERIVED_LAT) == false);
			astlib.allocateArray(asterixRecord, ASTERIX.AICRAFT_DERIVED_LAT, 2);
			assert(astlib.hasItem(asterixRecord, ASTERIX.AICRAFT_DERIVED_LAT) == true);
			astlib.setNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_LAT, pi2[0], 0);
			assert(astlib.getNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_LAT, 0) == pi2[0]);
			
			astlib.setNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_LAT, pi2[1], 1);
			assert(astlib.hasItem(asterixRecord, ASTERIX.AICRAFT_DERIVED_LAT) == true);	
			assert(astlib.getNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_LAT, 1) == pi2[1]);
		});

		it('Integer Number', function() {
			var i = -36745893;
			assert(astlib.hasItem(asterixRecord, ASTERIX.MODE5_GA) == false);
			astlib.setNumber(asterixRecord, ASTERIX.MODE5_GA, i);
			assert(astlib.hasItem(asterixRecord, ASTERIX.MODE5_GA) == true);	
			assert(astlib.getNumber(asterixRecord, ASTERIX.MODE5_GA) == i);
		});

		it('Integer Number Array', function() {
			var i2 = [ 3, -6 ];
			assert(astlib.hasItem(asterixRecord, ASTERIX.AICRAFT_DERIVED_TCPNUM) == false);
			astlib.allocateArray(asterixRecord, ASTERIX.AICRAFT_DERIVED_TCPNUM, 2);
			assert(astlib.hasItem(asterixRecord, ASTERIX.AICRAFT_DERIVED_TCPNUM) == true);
			astlib.setNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_TCPNUM, i2[0], 0);
			assert(astlib.getNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_TCPNUM, 0) == i2[0]);
			
			astlib.setNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_TCPNUM, i2[1], 1);
			assert(astlib.getNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_TCPNUM, 1) == i2[1]);
		});

		it('Unsigned Number', function() {
			var i = 54346745893;
			assert(astlib.hasItem(asterixRecord, ASTERIX.TRACK_STATUS_EMERGENCY) == false);
			astlib.setNumber(asterixRecord, ASTERIX.TRACK_STATUS_EMERGENCY, i);
			assert(astlib.hasItem(asterixRecord, ASTERIX.TRACK_STATUS_EMERGENCY) == true);	
			assert(astlib.getNumber(asterixRecord, ASTERIX.TRACK_STATUS_EMERGENCY) == i);
		});

		it('Unsigned Number Array', function() {
			var i2 = [ 34324563466, 67457456375 ];
			assert(astlib.hasItem(asterixRecord, ASTERIX.AICRAFT_DERIVED_TD) == false);
			astlib.allocateArray(asterixRecord, ASTERIX.AICRAFT_DERIVED_TD, 2);
			assert(astlib.hasItem(asterixRecord, ASTERIX.AICRAFT_DERIVED_TD) == true);
			astlib.setNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_TD, i2[0], 0);
			assert(astlib.getNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_TD, 0) == i2[0]);
			
			astlib.setNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_TD, i2[1], 1);
			assert(astlib.getNumberAt(asterixRecord, ASTERIX.AICRAFT_DERIVED_TD, 1) == i2[1]);
		});

		it('String', function() {
			var str = "Janťžščťžt";
			assert(astlib.hasItem(asterixRecord, ASTERIX.FPL_DATA_STAR) == false);	
			astlib.setString(asterixRecord, ASTERIX.FPL_DATA_STAR, str);
			assert(astlib.hasItem(asterixRecord, ASTERIX.FPL_DATA_STAR) == true);	
			assert(astlib.getString(asterixRecord, ASTERIX.FPL_DATA_STAR) == str);
		});

		it('String Number Array', function() {
			var s2 = [ "54363", "67457456375" ];
			assert(astlib.hasItem(asterixRecord, ASTERIX.MODES_MBDATA) == false);
			astlib.allocateArray(asterixRecord, ASTERIX.MODES_MBDATA, 2);
			assert(astlib.hasItem(asterixRecord, ASTERIX.MODES_MBDATA) == true);
			astlib.setStringAt(asterixRecord, ASTERIX.MODES_MBDATA, s2[0], 0);
			assert(astlib.getStringAt(asterixRecord, ASTERIX.MODES_MBDATA, 0) == s2[0]);
			
			astlib.setStringAt(asterixRecord, ASTERIX.MODES_MBDATA, s2[1], 1);
			assert(astlib.getStringAt(asterixRecord, ASTERIX.MODES_MBDATA, 1) == s2[1]);
		});

		it('Boolean', function() {
			var onoff = true;
			assert(astlib.hasItem(asterixRecord, ASTERIX.ACAS_RESOLUTION_ARA42) == false);	
			astlib.setBoolean(asterixRecord, ASTERIX.ACAS_RESOLUTION_ARA42, onoff);
			assert(astlib.hasItem(asterixRecord, ASTERIX.ACAS_RESOLUTION_ARA42) == true);	
			assert(astlib.getBoolean(asterixRecord, ASTERIX.ACAS_RESOLUTION_ARA42) == onoff);
		});

		/*
		 *  NO DEFINED BOOLEAN ARRAY YET
		it('Boolean Number Array', function() {
			var s2 = [ true, false ];
			assert(astlib.hasItem(asterixRecord, ASTERIX.MODES_MBDATA) == false);
			astlib.allocateArray(asterixRecord, ASTERIX.MODES_MBDATA, 2);
			assert(astlib.hasItem(asterixRecord, ASTERIX.MODES_MBDATA) == true);
			astlib.setBooleanAt(asterixRecord, ASTERIX.MODES_MBDATA, s2[0], 0);
			assert(astlib.getBooleanAt(asterixRecord, ASTERIX.MODES_MBDATA, 0) == s2[0]);
			
			astlib.setBooleanAt(asterixRecord, ASTERIX.MODES_MBDATA, s2[1], 1);
			assert(astlib.getBooleanAt(asterixRecord, ASTERIX.MODES_MBDATA, 1) == s2[1]);
		});
		 */
		it('Stringify', function() {
			assert.equal(astlib.toString(asterixRecord).length, 309);	
		});
	
		// TODO: JSONify
	}); 	
});

describe('Asterix Encoder/Decoder', function() {	
	var codecs = astlib.enumerateAllCodecs();
	
	describe('#codec 48', function() {
		it('empty record', function() {
			//console.log(astlib.toString(asterixRecord));
			var buffer = astlib.encodeAsterixRecord(asterixRecord, codecs[0]);			
			assert.ok(buffer != null);			
			assert.equal(buffer.length, 3);
		});
		
		it('plot', function() {
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
			//console.log(astlib.toString(plot));
			var buffer = astlib.encodeAsterixRecord(plot, 'Eurocontrol-48:1.21');			
			assert.ok(buffer != null);			
			assert.equal(buffer.length, 17);
			console.log(buffer);
			
			var records = astlib.decodeAsterixBuffer('Eurocontrol-48:1.21', buffer);
			assert.ok(records.length);
			var record = records[0];
			console.log(astlib.toString(record));
			
			assert.equal(astlib.getBoolean(plot, ASTERIX.TRACK_TEST), astlib.getBoolean(record, ASTERIX.TRACK_TEST));
			assert.equal(astlib.getBoolean(plot, ASTERIX.TRACK_SIMULATED), astlib.getBoolean(record, ASTERIX.TRACK_SIMULATED));
		
			assert.equal(astlib.getNumber(plot, ASTERIX.DSI_SAC), astlib.getNumber(record, ASTERIX.DSI_SAC));
			assert.equal(astlib.getNumber(plot, ASTERIX.DSI_SIC), astlib.getNumber(record, ASTERIX.DSI_SIC));
			assert.equal(astlib.getNumber(plot, ASTERIX.TIMEOFDAY), astlib.getNumber(record, ASTERIX.TIMEOFDAY));

			assert.equal(astlib.getNumber(plot, ASTERIX.TRACK_DETECTION), astlib.getNumber(record, ASTERIX.TRACK_DETECTION));

			assert.ok((astlib.getNumber(plot, ASTERIX.TRACK_POSITION_RANGE) - astlib.getNumber(record, ASTERIX.TRACK_POSITION_RANGE)) < 4);
			assert.equal(astlib.getNumber(plot, ASTERIX.TRACK_POSITION_AZIMUTH), astlib.getNumber(record, ASTERIX.TRACK_POSITION_AZIMUTH));

			assert.equal(astlib.getBoolean(plot, ASTERIX.MODE3A_V), astlib.getBoolean(record, ASTERIX.MODE3A_V));
			assert.equal(astlib.getBoolean(plot, ASTERIX.MODE3A_G), astlib.getBoolean(record, ASTERIX.MODE3A_G));
			assert.equal(astlib.getBoolean(plot, ASTERIX.MODE3A_L), astlib.getBoolean(record, ASTERIX.MODE3A_L));			
			assert.equal(astlib.getNumber(plot, ASTERIX.MODE3A_VALUE), astlib.getNumber(record, ASTERIX.MODE3A_VALUE));
		});
		
		it('track', function() {
			var plot = astlib.createAsterixRecord();
			astlib.setNumber(plot, ASTERIX.DSI_SAC, 44);
			astlib.setNumber(plot, ASTERIX.DSI_SIC, 144);
			astlib.setNumber(plot, ASTERIX.TIMEOFDAY, 3600);
			
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
			assert.ok(buffer != null);			
			assert.equal(buffer.length, 29);
			console.log(buffer);
			
			var records = astlib.decodeAsterixBuffer('Eurocontrol-48:1.21', buffer);
			assert.ok(records.length);
			var record = records[0];
			console.log(astlib.toString(record));
			
			assert.ok((astlib.getNumber(plot, ASTERIX.TRACK_POSITION_X) - astlib.getNumber(record, ASTERIX.TRACK_POSITION_X)) < 3);
			assert.ok((astlib.getNumber(plot, ASTERIX.TRACK_POSITION_Y) - astlib.getNumber(record, ASTERIX.TRACK_POSITION_Y)) < 3);
			
			assert.equal(astlib.getBoolean(plot, ASTERIX.MODE2_V), astlib.getBoolean(record, ASTERIX.MODE2_V));
			assert.equal(astlib.getBoolean(plot, ASTERIX.MODE2_G), astlib.getBoolean(record, ASTERIX.MODE2_G));
			assert.equal(astlib.getBoolean(plot, ASTERIX.MODE2_L), astlib.getBoolean(record, ASTERIX.MODE2_L));			
			assert.equal(astlib.getNumber(plot, ASTERIX.MODE2_VALUE), astlib.getNumber(record, ASTERIX.MODE2_VALUE));
			
			assert.equal(astlib.getNumber(plot, ASTERIX.TRACK_NUMBER), astlib.getNumber(record, ASTERIX.TRACK_NUMBER));
			assert.equal(astlib.getString(plot, ASTERIX.AIRCRAFT_ADDRESS), astlib.getString(record, ASTERIX.AIRCRAFT_ADDRESS));
			assert.equal(astlib.getString(plot, ASTERIX.AIRCRAFT_IDENTIFICATION), astlib.getString(record, ASTERIX.AIRCRAFT_IDENTIFICATION));
		});		
	}); 	
});

