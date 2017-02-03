///
/// \package astlib
/// \file VariableItemDescription.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 3Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "FixedItemDescription.h"

namespace astlib
{

class VariableItemDescription:
    public ItemDescription
{
public:
    VariableItemDescription(int id, const std::string& description, const FixedVector& fixeds);
    virtual ~VariableItemDescription();

private:
    virtual ItemFormat getType() const { return ItemFormat::Variable; }

    FixedVector _fixedArray;
};

} /* namespace astlib */

