///
/// \package astlib
/// \file SimpleValueDecoder.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 13. 2. 2017 - 18:47:22
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#include "SimpleValueDecoder.h"

namespace astlib
{

SimpleValueDecoder::SimpleValueDecoder()
{
}

SimpleValueDecoder::~SimpleValueDecoder()
{
}

void SimpleValueDecoder::begin()
{
    _msg = std::make_shared<SimpleAsterixRecord>();
}

void SimpleValueDecoder::beginItem(const ItemDescription& uapItem)
{
}

void SimpleValueDecoder::beginRepetitive(size_t size)
{
}

void SimpleValueDecoder::beginArray(AsterixItemCode code, size_t size)
{
    _msg->initializeArray(code, size);
}

void SimpleValueDecoder::decodeBoolean(const CodecContext& context, bool value, int index)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeSigned(const CodecContext& context, Poco::Int64 value, int index)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeUnsigned(const CodecContext& context, Poco::UInt64 value, int index)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeReal(const CodecContext& context, double value, int index)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeString(const CodecContext& context, const std::string& value, int index)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::end()
{
    onMessageDecoded(_msg);
    _msg = nullptr;
}

} /* namespace astlib */
