///
/// \package astlib
/// \file ValueEncoder.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 20Feb.,2017 
/// \brief definicia typu
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

    virtual bool encode(const CodecContext& ctx, Poco::UInt64& value) = 0;
};

} /* namespace astlib */

