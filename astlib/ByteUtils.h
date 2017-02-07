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
};

} /* namespace astlib */

