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

PrimitiveItem::PrimitiveItem(const std::string& name, const std::string& description, PrimitiveType type, bool arrayType) :
    _name(name),
    _description(description),
    _type(type),
    _arrayType(arrayType)
{
}

PrimitiveItem::~PrimitiveItem()
{
}

const std::string& PrimitiveItem::getName() const
{
    return _name;
}

const std::string& PrimitiveItem::getDescription() const
{
    return _description;
}

PrimitiveType PrimitiveItem::getType() const
{
    return _type;
}

bool PrimitiveItem::isArray() const
{
    return _arrayType;
}

} /* namespace astlib */

