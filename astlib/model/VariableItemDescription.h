///
/// \package astlib
/// \file VariableItemDescription.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 3Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "FixedItemDescription.h"

namespace astlib
{

class ASTLIB_API VariableItemDescription :
    public ItemDescription
{
public:
    VariableItemDescription(int id, const std::string& description, const FixedVector& fixeds);
    virtual ~VariableItemDescription();

    const FixedVector& getFixedVector() const { return _fixedArray; }

private:
    virtual ItemFormat getType() const { return ItemFormat::Variable; }

    FixedVector _fixedArray;
};

} /* namespace astlib */

