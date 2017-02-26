///
/// \package astlib
/// \file TypedValueDecoder.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 7Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///


#pragma once

#include "ValueDecoder.h"

namespace astlib
{

/**
 * Wrapper for easy value type handling.
 * Implements decode() method, converts value to apropriate type and call its typed callback.
 */
class TypedValueDecoder :
    public ValueDecoder
{
public:
    virtual void decode(const CodecContext& ctx, Poco::UInt64 value, int index);

    virtual void decodeBoolean(const CodecContext& ctx, bool value, int index) = 0;
    virtual void decodeSigned(const CodecContext& ctx, Poco::Int64 value, int index) = 0;
    virtual void decodeUnsigned(const CodecContext& ctx, Poco::UInt64 value, int index) = 0;
    virtual void decodeReal(const CodecContext& ctx, double value, int index) = 0;
    virtual void decodeString(const CodecContext& ctx, const std::string& value, int index) = 0;
};

}



