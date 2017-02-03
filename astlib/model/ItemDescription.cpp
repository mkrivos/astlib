///
/// \package astlib
/// \file ItemDescription.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 1. 2. 2017 - 18:45:34
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#include "ItemDescription.h"

namespace astlib
{

ItemDescription::ItemDescription(int id, const std::string& description) :
    _id(id),
    _description(description)
{
}

const std::string& ItemDescription::getDescription() const
{
    return _description;
}

int ItemDescription::getId() const
{
    return _id;
}

} /* namespace artus */
