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
#include <map>

namespace astlib
{

class BitsDescription
{
public:
    using ValueMap = std::map<std::string, int>;

    BitsDescription();
    ~BitsDescription();

    Encoding encoding = Encoding::Unsigned;
    std::string name;
    ValueMap values;
    int bit = -1;
    int from = -1;
    int to = -1;
    bool fx = false;
    bool repeat = false;

    std::string toString() const;
};

using BitsDescriptionArray = std::vector<BitsDescription>;

} /* namespace astlib */

