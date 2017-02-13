///
/// \package astlib
/// \file PrimitiveItem.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 13Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "PrimitiveItem.h"

namespace astlib
{

PrimitiveItem::PrimitiveItem()
{
}

PrimitiveItem::PrimitiveItem(const std::string& name, PrimitiveType type) :
    _name(name),
    _type(type)
{
}

PrimitiveItem::~PrimitiveItem()
{
}

const std::string& PrimitiveItem::getName() const
{
    return _name;
}

PrimitiveType PrimitiveItem::getType() const
{
    return _type;
}

} /* namespace astlib */

