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

/**
 * Trival decoder that creates SimpleAsterixMessage on each decoded asterix record.
 */
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
    virtual void decodeBoolean(const CodecContext& context, bool value);
    virtual void decodeSigned(const CodecContext& context, Poco::Int64 value);
    virtual void decodeUnsigned(const CodecContext& context, Poco::UInt64 value);
    virtual void decodeReal(const CodecContext& context, double value);
    virtual void decodeString(const CodecContext& context, const std::string& value);
    virtual void end();

    virtual void onMessageDecoded(SimpleAsterixMessagePtr ptr) = 0;

private:
    SimpleAsterixMessagePtr _msg;
};

} /* namespace astlib */
