//
// Copyright (c) 2013-2016 Pavel Medvedev. All rights reserved.
//
// This file is part of v8pp (https://github.com/pmed/v8pp) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

var should = require("should");
var astlib = require('./build/Release/addon.node');
const ASTERIX = require('./asterixitems.js');

var asterixRecord = astlib.createAsterixRecord();
should.exists(asterixRecord);

astlib.setNumber(asterixRecord, ASTERIX.TRACK_POSITION_LATITUDE, 3.14);
should(astlib.hasItem(asterixRecord, ASTERIX.TRACK_POSITION_LATITUDE) == true);	
should(astlib.getNumber(asterixRecord, ASTERIX.TRACK_POSITION_LATITUDE) == 3.14);

astlib.setBoolean(asterixRecord, ASTERIX.ACAS_RESOLUTION_ARA42, false);
var result = astlib.toString(asterixRecord);
var array = astlib.enumerateAllCodecs();
