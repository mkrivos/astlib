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

#include "model/BitsDescription.h"
#include "model/ItemDescription.h"

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
    virtual void item(const ItemDescription& uapItem) = 0;
    virtual void repetitive(int) = 0;
    virtual void decode(Poco::UInt64 value, const BitsDescription& bits) = 0;
    virtual void end() = 0;
};

/**
 * Wrapper for easy value type handling.
 * Implements decode() method, converts value to apropriate type and call its typed callback.
 */
class TypedValueDecoder :
    public ValueDecoder
{
public:
    virtual void decode(Poco::UInt64 value, const BitsDescription& bits);

    virtual void decodeBoolean(const std::string& identification, bool value) = 0;
    virtual void decodeSigned(const std::string& identification, Poco::Int64 value) = 0;
    virtual void decodeUnsigned(const std::string& identification, Poco::UInt64 value) = 0;
    virtual void decodeReal(const std::string& identification, double value) = 0;
    virtual void decodeString(const std::string& identification, const std::string& value) = 0;
};

}



