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

#include "astlib/SimpleAsterixRecord.h"
#include "TypedValueDecoder.h"

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
    virtual void beginItem(const ItemDescription& uapItem);
    virtual void beginRepetitive(size_t size);
    virtual void beginArray(AsterixItemCode code, size_t size);
    virtual void decodeBoolean(const CodecContext& context, bool value, int index);
    virtual void decodeSigned(const CodecContext& context, Poco::Int64 value, int index);
    virtual void decodeUnsigned(const CodecContext& context, Poco::UInt64 value, int index);
    virtual void decodeReal(const CodecContext& context, double value, int index);
    virtual void decodeString(const CodecContext& context, const std::string& value, int index);
    virtual void end();

    virtual void onMessageDecoded(SimpleAsterixRecordPtr ptr) = 0;

private:
    SimpleAsterixRecordPtr _msg;
};

} /* namespace astlib */
