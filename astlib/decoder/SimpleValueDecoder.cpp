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
    _msg = std::make_shared<SimpleAsterixMessage>();
}

void SimpleValueDecoder::dataItem(const ItemDescription& uapItem)
{
}

void SimpleValueDecoder::beginRepetitive(int)
{
}

void SimpleValueDecoder::repetitiveItem(int index)
{
}

void SimpleValueDecoder::endRepetitive()
{
}

void SimpleValueDecoder::decodeBoolean(const CodecContext& context, bool value)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeSigned(const CodecContext& context, Poco::Int64 value)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeUnsigned(const CodecContext& context, Poco::UInt64 value)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeReal(const CodecContext& context, double value)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeString(const CodecContext& context, const std::string& value)
{
    _msg->addSimpleItem(context.bits.code, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::end()
{
    onMessageDecoded(_msg);
    _msg = nullptr;
}

} /* namespace astlib */
