///
/// \package astlib
/// \file FixedItemDescription.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 2Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "ItemDescription.h"
#include "Fixed.h"
#include <vector>

namespace astlib
{

class ASTLIB_API FixedItemDescription:
    public ItemDescription
{
public:
    FixedItemDescription(int id, const std::string& description, const Fixed& fixed);
    virtual ~FixedItemDescription();

    const Fixed& getFixed() const { return _fixed; }

private:
    virtual ItemFormat getType() const { return ItemFormat::Fixed; }

    const Fixed _fixed;
};

} /* namespace astlib */

