///
/// \package astlib
/// \file EmptyValueDecoder.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
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
    virtual void dataItem(const ItemDescription& uapItem)
    {
    }
    virtual void beginRepetitive(int count)
    {
    }
    virtual void repetitiveItem(int index)
    {
    }
    virtual void endRepetitive()
    {
    }
    virtual void decode(const CodecContext& bits, Poco::UInt64 value)
    {
    }
    virtual void end()
    {
    }
};

}

