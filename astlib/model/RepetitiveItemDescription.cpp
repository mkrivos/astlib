///
/// \package astlib
/// \file RepetitiveItemDescription.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 3Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "RepetitiveItemDescription.h"

namespace astlib
{

RepetitiveItemDescription::RepetitiveItemDescription(int id, const std::string& description, const FixedVector& fixeds) :
    ItemDescription(id, description),
    _fixedArray(fixeds)
{
}

RepetitiveItemDescription::~RepetitiveItemDescription()
{
}

} /* namespace astlib */
