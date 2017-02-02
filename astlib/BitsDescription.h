///
/// \package astlib
/// \file BitsDescription.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 2Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "GeneratedTypes.h"

namespace astlib
{

class BitsDescription
{
public:
    BitsDescription();
    ~BitsDescription();

    Encoding encoding = Encoding::Unsigned;
    std::string name;
    int bit = 0;
    int from = 0;
    int to = 0;
    bool fx = false;
    bool repeat = false;
};

using BitsDescriptionArray = std::vector<BitsDescription>;

} /* namespace astlib */

