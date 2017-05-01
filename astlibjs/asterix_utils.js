///
/// \package astlib
/// \file asterix_utils.js
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 24.2.2017
/// \brief JS Wrapper over astlib C++
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///


function itemIsArray(code) {
    return code & 0x80000000;
}

function itemIsScalar(code) {
    return !itemIsArray();
}

function itemType(code) 
{
    return (code>>24) & 0xF;
}

function itemIsValid(code) 
{
    return code != 0;
}

/**
 * Reads ASTERIX codes and declare ones in global namespace.
 * (this magic code allows no prefixes)
 * @param astlib
 * @returns
 */
function declareAsterixCodes(astlib) 
{
	for (var key in astlib)
	{
		if (key.startsWith("EXPORT_"))
		{
			let str = key.slice(7) + "=" + astlib[key];
			eval(str);
		}
	}
}

exports = module.exports;
exports.itemIsArray = itemIsArray
exports.itemIsScalar = itemIsScalar
exports.itemType = itemType
exports.itemIsValid = itemIsValid
exports.declareAsterixCodes = declareAsterixCodes;

exports.Unknown = 0;
exports.Boolean = 1;
exports.Integer = 2;
exports.Unsigned = 3;
exports.Real = 4;
exports.String = 5;