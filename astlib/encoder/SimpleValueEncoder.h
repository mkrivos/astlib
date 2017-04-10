///
/// \package astlib
/// \file SimpleValueEncoder.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 24Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "TypedValueEncoder.h"
#include "astlib/SimpleAsterixRecord.h"

namespace astlib
{

class ASTLIB_API SimpleValueEncoder:
    public TypedValueEncoder
{
public:
    SimpleValueEncoder(SimpleAsterixRecordPtr record);

    virtual size_t getArraySize(AsterixItemCode code) const;
    virtual bool encodeBoolean(const CodecContext& ctx, bool& value, int index);
    virtual bool encodeSigned(const CodecContext& ctx, Poco::Int64& value, int index);
    virtual bool encodeUnsigned(const CodecContext& ctx, Poco::UInt64& value, int index);
    virtual bool encodeReal(const CodecContext& ctx, double& value, int index);
    virtual bool encodeString(const CodecContext& ctx, std::string& value, int index);

private:
    SimpleAsterixRecordPtr _record;
};

} /* namespace astlib */

