///
/// \package astlib
/// \file AsterixItemCode.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13. 2. 2017 - 19:49:36
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///


#pragma once

#include "GeneratedTypes.h"
#include "Astlib.h"

namespace astlib
{

/**
 * Class that encapsulate unique asterix pair<item id, item type>.
 * Use this class with generated codes ASTERIX_CODE_* to identification of decoded asterix items.
 */
struct AsterixItemCode
{
    constexpr AsterixItemCode(Poco::UInt32 value = 0) : value(value) {}
    constexpr AsterixItemCode(const AsterixItemCode& old ) : value(old.value) {}

    constexpr AsterixItemCode(int code, int type, bool array = false) :
        value((array << 31) | (type << 24) | (code & 0x0FFF))
    {
    }

    constexpr int code() const
    {
        return value & 0xFFF;
    }

    constexpr int type() const
    {
        return (value>>24) & 0xF;
    }

    constexpr bool isArray() const
    {
        return bool(value & 0x80000000);
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

