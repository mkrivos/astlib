///
/// \package astlib
/// \file ByteUtils.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 7Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "ByteUtils.h"

namespace astlib
{

ByteUtils::ByteUtils()
{
}

ByteUtils::~ByteUtils()
{
}

size_t ByteUtils::calculateFspec(const Byte fspecPtr[])
{
    size_t fspecLen = 1;

    for (int k = 0; fspecPtr[k] & FX_BIT; k++)
    {
        fspecLen++;
    }

    return fspecLen;
}

} /* namespace astlib */
