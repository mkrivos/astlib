///
/// \package astlib
/// \file ItemDescription.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 1. 2. 2017 - 18:45:34
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#pragma once

#include "GeneratedTypes.h"
#include <string>
#include <memory>

namespace astlib
{

class ItemDescription;
using ItemDescriptionPtr = std::shared_ptr<ItemDescription>;

class ItemDescription
{
public:
    ItemDescription(const ItemType& type);
    virtual ~ItemDescription() = default;

    static ItemDescriptionPtr createFixedItem();

private:

    ItemType _itemType;
    std::string _id;
    std::string _description;
};

} /* namespace artus */
