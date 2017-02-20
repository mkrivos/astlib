///
/// \package astlib
/// \file FspecGenerator.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 20Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "FspecGenerator.h"

namespace astlib
{

FspecGenerator::FspecGenerator()
{
    _fspec.push_back(0);
}

FspecGenerator::~FspecGenerator()
{
}

void FspecGenerator::addItem()
{
    skipItem();
    _fspec.back() |= _byteMask;
}

void FspecGenerator::skipItem()
{
    _byteMask >>= 1;
    if (_byteMask & 1)
    {
        _fspec.back() |= _byteMask;
        _fspec.push_back(0);
        _byteMask = 0x80;
    }
}

void FspecGenerator::skipItems(int count)
{
    for(int i = 0; i < count; i++)
    {
        skipItem();
    }
}

size_t FspecGenerator::size() const
{
    return _fspec.size();
}

const Byte* FspecGenerator::data() const
{
    return _fspec.data();
}

} /* namespace astlib */
