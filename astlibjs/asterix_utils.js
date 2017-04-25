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

exports = module.exports;
exports.itemIsArray = itemIsArray
exports.itemIsScalar = itemIsScalar
exports.itemType = itemType
exports.itemIsValid = itemIsValid

exports.Unknown = 0;
exports.Boolean = 1;
exports.Integer = 2;
exports.Unsigned = 3;
exports.Real = 4;
exports.String = 5;