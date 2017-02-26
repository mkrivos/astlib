///
/// \package astlib
/// \file BitsDescription.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 2Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "BitsDescription.h"

namespace astlib
{

void BitsDescription::addEnumeration(const std::string& key, int value)
{
    values[key] = value;
}

std::string BitsDescription::toString() const
{
    if (bit != -1)
    {
        return name + " bit " + std::to_string(bit);
    }
    else
    {
        return name + " from " + std::to_string(from) + " to " + std::to_string(to);
    }
}

int BitsDescription::effectiveBitsWidth() const
{
    return from-to+1;
}

Poco::UInt64 BitsDescription::bitMask() const
{
    return (1ULL << effectiveBitsWidth()) - 1;
}

} /* namespace astlib */
