///
/// \package astlib
/// \file SimpleValueEncoder.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 24Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "SimpleValueEncoder.h"

namespace astlib
{

SimpleValueEncoder::SimpleValueEncoder(SimpleAsterixRecordPtr record) :
    _record(record)
{
}

size_t SimpleValueEncoder::getArraySize(AsterixItemCode code) const
{
    return _record->getArraySize(code);
}

bool SimpleValueEncoder::encodeBoolean(const CodecContext& ctx, bool& value, int index)
{
    return _record->getBoolean(ctx.bits.code, value, index);
}

bool SimpleValueEncoder::encodeSigned(const CodecContext& ctx, Poco::Int64& value, int index)
{
    return _record->getSigned(ctx.bits.code, value, index);
}

bool SimpleValueEncoder::encodeUnsigned(const CodecContext& ctx, Poco::UInt64& value, int index)
{
    return _record->getUnsigned(ctx.bits.code, value, index);
}

bool SimpleValueEncoder::encodeReal(const CodecContext& ctx, double& value, int index)
{
    return _record->getReal(ctx.bits.code, value, index);
}

bool SimpleValueEncoder::encodeString(const CodecContext& ctx, std::string& value, int index)
{
    return _record->getString(ctx.bits.code, value, index);
}

} /* namespace astlib */
