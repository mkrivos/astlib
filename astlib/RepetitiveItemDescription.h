///
/// \package astlib
/// \file RepetitiveItemDescription.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 3Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "Fixed.h"
#include "ItemDescription.h"

namespace astlib
{

class RepetitiveItemDescription:
    public ItemDescription
{
public:
    RepetitiveItemDescription(int id, const std::string& description, const FixedVector& fixeds);
    virtual ~RepetitiveItemDescription();

private:
    virtual ItemFormat getType() const { return ItemFormat::Repetitive; }

    FixedVector _fixedArray;
};

} /* namespace astlib */

