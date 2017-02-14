///
/// \package astlib
/// \file SimpleValueDecoder.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 13. 2. 2017 - 18:47:21
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#pragma once

#include "SimpleAsterixMessage.h"
#include "ValueDecoder.h"

namespace astlib
{

class SimpleValueDecoder:
    public TypedValueDecoder
{
public:
    SimpleValueDecoder();
    virtual ~SimpleValueDecoder();

    virtual void begin();
    virtual void dataItem(const ItemDescription& uapItem);
    virtual void beginRepetitive(int);
    virtual void repetitiveItem(int index);
    virtual void endRepetitive();
    virtual void decodeBoolean(const std::string& identification, bool value);
    virtual void decodeSigned(const std::string& identification, Poco::Int64 value);
    virtual void decodeUnsigned(const std::string& identification, Poco::UInt64 value);
    virtual void decodeReal(const std::string& identification, double value);
    virtual void decodeString(const std::string& identification, const std::string& value);
    virtual void end();

    virtual void onMessageDecoded(SimpleAsterixMessagePtr ptr) = 0;

private:
    SimpleAsterixMessagePtr _msg;
};

} /* namespace astlib */
