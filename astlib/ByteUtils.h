///
/// \package astlib
/// \file ByteUtils.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 7Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "Astlib.h"
#include <Poco/Types.h>
#include <cstddef>
#include <vector>

namespace astlib
{

using Byte = unsigned char;

constexpr int FX_BIT = 1;

class ASTLIB_API ByteUtils
{
public:
    ByteUtils();
    ~ByteUtils();

    static size_t calculateFspec(const Byte fspecPtr[]);

    static Poco::Int64 toSigned(Poco::UInt64, int effectiveBits);

    static Poco::UInt64 oct2dec(Poco::UInt32 modeValue);

    static Poco::UInt32 dec2oct(Poco::UInt64 modeValue);

    static std::string fromSixBitString(const Byte buffer[]);

    static std::string toSixBitString(const std::string sixbit);

    static void pokeBigEndian(Byte buffer[], Poco::UInt64 value, size_t len);

    static void printHex(const std::vector<Byte>& buffer);
};

} /* namespace astlib */

