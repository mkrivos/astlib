///
/// \package astlib
/// \file ValueDecoder.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 7Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///


#pragma once

#include "astlib/CodecContext.h"

namespace astlib
{

/**
 * Base interface for dekoder callback mechanism.
 * The methods are called on:
 * - begin of record
 * - start of each Uap Data Item
 * - start of each round for repetitive items
 * - each decoded primite value
 * - end of record
 */
class ValueDecoder
{
public:
    virtual ~ValueDecoder() = default;

    virtual void begin() = 0;
    virtual void beginItem(const ItemDescription& uapItem) = 0;
    virtual void beginRepetitive(size_t size) = 0;
    virtual void decode(const CodecContext& ctx, Poco::UInt64 value, int index) = 0;
    virtual void end() = 0;

    virtual void repetitiveItem(int index)
    {
    }
    virtual void beginArray(AsterixItemCode code, size_t size) = 0;
    virtual void endRepetitive()
    {
    }
};

}



