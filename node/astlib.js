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


describe('Asterix Encoder', function() {	
	var codecs = astlib.enumerateAllCodecs();
	
	describe('#encode', function() {
		it('empty record', function() {
			//console.log(astlib.toString(asterixRecord));
			var buffer = astlib.encodeAsterixRecord(asterixRecord, codecs[0]);			
			assert.ok(buffer != null);			
			assert.equal(buffer.length, 3);
		});
		
		it('cat. 48 plot', function() {
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
			astlib.setNumber(plot, ASTERIX.MODE3A_VALUE, 9053);
			console.log(astlib.toString(plot));
			var buffer = astlib.encodeAsterixRecord(plot, 'Eurocontrol-48:1.21');			
			assert.ok(buffer != null);			
			assert.equal(buffer.length, 17);
			console.log(buffer);
			
			var record = astlib.decodeAsterixBuffer('Eurocontrol-48:1.21', buffer);
			console.log(astlib.toString(record[0]));
		});
	}); 	
});

