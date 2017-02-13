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
    constexpr AsterixItemCode() {}

    constexpr AsterixItemCode(int code, int subcode, int type) :
        value((type << 24) | (subcode << 16) | code)
    {
    }

    constexpr int code() const
    {
        return value & 0xFFFF;
    }

    constexpr int subCode() const
    {
        return (value>>16) & 0xFF;
    }

    constexpr int type() const
    {
        return (value>>24) & 0xFF;
    }

    const Poco::UInt32 value = 0;
};

inline bool operator < (const AsterixItemCode left, const AsterixItemCode right)
{
    return left.value < right.value;
}

}

