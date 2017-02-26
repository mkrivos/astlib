///
/// \package astlib
/// \file VariableItemDescription.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 3Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "VariableItemDescription.h"

namespace astlib
{

VariableItemDescription::VariableItemDescription(int id, const std::string& description, const FixedVector& fixeds) :
    ItemDescription(id, description),
    _fixedArray(fixeds)
{
}

VariableItemDescription::~VariableItemDescription()
{
}

} /* namespace astlib */
