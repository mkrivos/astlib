///
/// \package astlib
/// \file EmptyValueDecoder.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13. 2. 2017 - 18:43:24
/// \brief Zero decoder, simply throws any input.
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///


#pragma once

#include "ValueDecoder.h"

namespace astlib
{

/**
 * Zero decoder, simply throws decoded values.
 */
class EmptyValueDecoder :
    public ValueDecoder
{
    virtual void begin()
    {
    }
    virtual void beginItem(const ItemDescription& uapItem)
    {
    }
    virtual void beginRepetitive(size_t size)
    {
    }
    virtual void decode(const CodecContext& bits, Poco::UInt64 value, int index)
    {
    }
    virtual void end()
    {
    }
    virtual void beginArray(AsterixItemCode code, size_t size)
    {
    }
};

}

