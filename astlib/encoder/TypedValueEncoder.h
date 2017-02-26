///
/// \package astlib
/// \file TypedValueEncoder.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 20Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "ValueEncoder.h"


namespace astlib
{

class TypedValueEncoder :
    public ValueEncoder
{
public:
    /// Call type specific encoding methods and transform result to binary representation
    virtual bool encode(const CodecContext& ctx, Poco::UInt64& value, int index);

    virtual bool encodeBoolean(const CodecContext& ctx, bool& value, int index) = 0;
    virtual bool encodeSigned(const CodecContext& ctx, Poco::Int64& value, int index) = 0;
    virtual bool encodeUnsigned(const CodecContext& ctx, Poco::UInt64& value, int index) = 0;
    virtual bool encodeReal(const CodecContext& ctx, double& value, int index) = 0;
    virtual bool encodeString(const CodecContext& ctx, std::string& value, int index) = 0;
};

} /* namespace astlib */

