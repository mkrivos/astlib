///
/// \package astlib
/// \file FspecGenerator.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 20Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "FspecGenerator.h"
#include "astlib/Exception.h"
#include <algorithm>

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

std::vector<Byte> FspecGenerator::getArray() const
{
    return reduce(_fspec);
}

std::vector<Byte> FspecGenerator::reduce(const std::vector<Byte>& sequence)
{
    std::vector<Byte> array;

    auto iterator = sequence.rbegin();
    auto end = sequence.rend();
    bool contains = false;

    if (sequence.empty())
        return array;

    if (sequence.back() & FX_BIT)
        throw Exception("FspecGenerator: FX bit is set at the end of byte sequence");

    while (iterator != end)
    {
        Byte byte = *iterator;

        if (contains == false)
        {
            contains = byte & 0xFE;
        }
        else
        {
            byte |= FX_BIT;
        }

        if (contains)
        {
            array.push_back(byte);
        }
        ++iterator;
    }

    std::reverse(array.begin(), array.end());

    if (array.size())
        array.back() &= 0xFE; // clear FX at the end
    return array;
}

} /* namespace astlib */
