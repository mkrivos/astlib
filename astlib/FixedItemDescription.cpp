///
/// \package astlib
/// \file FixedItemDescription.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 2Feb.,2017 
/// \brief definicia typu
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
