///
/// \package astlib
/// \file ByteUtils.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 7Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include <Poco/Types.h>
#include <cstddef>

namespace astlib
{

using Byte = unsigned char;

constexpr int FX_BIT = 1;

class ByteUtils
{
public:
    ByteUtils();
    ~ByteUtils();

    static size_t calculateFspec(const Byte fspecPtr[]);

    static Poco::Int64 toSigned(Poco::UInt64, int effectiveBits);

    static Poco::UInt64 oct2dec(Poco::UInt32 modeValue);

    static Poco::UInt32 dec2oct(Poco::UInt64 modeValue);

    static std::string fromSixBitString(const Byte buffer[]);

    static void pokeBigEndian(Byte buffer[], Poco::UInt64 value, size_t len);
};

} /* namespace astlib */

