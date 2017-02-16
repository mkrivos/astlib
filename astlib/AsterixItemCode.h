///
/// \package astlib
/// \file AsterixItemCode.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 13. 2. 2017 - 19:49:36
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///


#pragma once

#include "GeneratedTypes.h"

namespace astlib
{

struct AsterixItemCode
{
    constexpr AsterixItemCode(Poco::UInt32 value = 0) : value(value) {}
    constexpr AsterixItemCode(const AsterixItemCode& old ) : value(old.value) {}

    constexpr AsterixItemCode(int code, int type) :
        value((type << 24) | (code & 0x0FFF))
    {
    }

    constexpr int code() const
    {
        return value & 0xFFF;
    }

    constexpr int type() const
    {
        return (value>>24) & 0xFF;
    }

    constexpr bool isValid() const
    {
        return value != 0;
    }

    const Poco::UInt32 value = 0;
};

inline bool operator < (const AsterixItemCode left, const AsterixItemCode right)
{
    return left.value < right.value;
}

}

