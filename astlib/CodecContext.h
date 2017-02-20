///
/// \package astlib
/// \file CodecContext.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 20Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/model/BitsDescription.h"
#include "astlib/model/ItemDescription.h"


namespace astlib
{

class CodecContext
{
public:
    CodecContext(const ItemDescription& uapItem, const BitsDescription& bits, int depth) :
        uapItem(uapItem),
        bits(bits),
        depth(depth),
        width(bits.effectiveBitsWidth())
    {
    }

    const ItemDescription& uapItem;
    const BitsDescription& bits;
    int depth = 0;
    int width = 1;
};

} /* namespace astlib */

