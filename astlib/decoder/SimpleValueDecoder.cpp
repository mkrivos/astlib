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

void SimpleValueDecoder::decodeBoolean(const std::string& identification, bool value)
{
    _msg->addSimpleItem(0, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeSigned(const std::string& identification, Poco::Int64 value)
{
    _msg->addSimpleItem(1, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeUnsigned(const std::string& identification, Poco::UInt64 value)
{
    _msg->addSimpleItem(2, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeReal(const std::string& identification, double value)
{
    _msg->addSimpleItem(3, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::decodeString(const std::string& identification, const std::string& value)
{
    _msg->addSimpleItem(4, std::move(Poco::Dynamic::Var(value)));
}

void SimpleValueDecoder::end()
{
    onMessageDecoded(_msg);
    _msg = nullptr;
}

} /* namespace astlib */
