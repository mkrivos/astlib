///
/// \package astlib
/// \file Fixed.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 2Feb.,2017 
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

