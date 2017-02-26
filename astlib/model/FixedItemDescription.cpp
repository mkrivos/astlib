///
/// \package astlib
/// \file FixedItemDescription.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 2Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "FixedItemDescription.h"

namespace astlib
{

FixedItemDescription::FixedItemDescription(int id, const std::string& description, const Fixed& fixed) :
    ItemDescription(id, description),
    _fixed(fixed)
{
}

FixedItemDescription::~FixedItemDescription()
{
}

} /* namespace astlib */
