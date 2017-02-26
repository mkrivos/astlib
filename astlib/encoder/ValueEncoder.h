///
/// \package astlib
/// \file ValueEncoder.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 20Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/CodecContext.h"


namespace astlib
{

class ValueEncoder
{
public:
    virtual ~ValueEncoder() = default;

    virtual bool encode(const CodecContext& ctx, Poco::UInt64& value, int index) = 0;

    /// When encoding repetitive items, this method is used to return size of vector items
    virtual size_t getArraySize(AsterixItemCode code) const = 0;
};

} /* namespace astlib */

