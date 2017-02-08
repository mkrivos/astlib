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

namespace astlib
{

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

}



