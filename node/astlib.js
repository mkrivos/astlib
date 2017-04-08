//
// Copyright (c) 2013-2016 Pavel Medvedev. All rights reserved.
//
// This file is part of v8pp (https://github.com/pmed/v8pp) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
var astlib = require('./build/Release/addon.node');

const Unknown = 0;
const Boolean = 1;
const Integer = 2;
const Unsigned = 3;
const Real = 4;
const String = 5;

const ACAS_RESOLUTION_ACAS3_CODE = ((0 << 31) | (Unsigned << 24) | (1 & 0x0FFF));
const ACAS_RESOLUTION_ARA41_CODE = ((0 << 31) | (Boolean << 24) | (2 & 0x0FFF));
const ACAS_RESOLUTION_ARA42_CODE = ((0 << 31) | (Boolean << 24) | (3 & 0x0FFF));

var obj1 = astlib.createAsterixRecord();
astlib.setNumberItem(obj1, ACAS_RESOLUTION_ARA41_CODE, 3.14);
astlib.setBooleanItem(obj1, ACAS_RESOLUTION_ARA42_CODE, false);
var result = astlib.toString(obj1);

console.log(result); // 30
console.log(astlib.hasItem(obj1, ACAS_RESOLUTION_ARA41_CODE));
console.log(astlib.hasItem(obj1, ACAS_RESOLUTION_ARA42_CODE));
console.log(astlib.getBooleanItem(obj1, ACAS_RESOLUTION_ARA42_CODE));

for(var i = 0; i < 100000; i++) {
	astlib.setBooleanItem(obj1, ACAS_RESOLUTION_ARA42_CODE, false);	
}

dorobit code/decode