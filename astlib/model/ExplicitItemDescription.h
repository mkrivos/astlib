///
/// \package astlib
/// \file RepetitiveItemDescription.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 3Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "Fixed.h"
#include "ItemDescription.h"

namespace astlib
{

class ASTLIB_API ExplicitItemDescription:
    public ItemDescription
{
public:
    ExplicitItemDescription(int id, const std::string& description, const FixedVector& fixeds);
    virtual ~ExplicitItemDescription();

    const FixedVector& getFixedVector() const { return _fixedArray; }

private:
    virtual ItemFormat getType() const { return ItemFormat::Explicit; }

    FixedVector _fixedArray;
};

} /* namespace astlib */

