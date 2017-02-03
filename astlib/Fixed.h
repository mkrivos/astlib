///
/// \package astlib
/// \file Fixed.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 2Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "BitsDescription.h"
#include <vector>

namespace astlib
{

struct Fixed
{
    BitsDescriptionArray bitsDescriptions;
    int length = 0;

    Fixed(const BitsDescriptionArray& bits, int length) :
        bitsDescriptions(bits),
        length(length)
    {
    }
};

using FixedVector = std::vector<Fixed>;

} /* namespace astlib */

