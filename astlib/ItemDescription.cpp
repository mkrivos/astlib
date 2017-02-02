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

ItemDescription::ItemDescription(const ItemType& type) :
    _itemType(type)
{
}


ItemDescriptionPtr ItemDescription::createFixedItem()
{
    ItemDescriptionPtr item = std::make_shared<ItemDescription>(ItemType::Fixed);
    return item;
}

} /* namespace artus */
