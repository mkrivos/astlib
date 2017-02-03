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
#include "BitsDescription.h"

#include <string>
#include <memory>
#include <vector>

namespace astlib
{

class ItemDescription;
using ItemDescriptionPtr = std::shared_ptr<ItemDescription>;

class ItemDescription
{
public:
    ItemDescription(int id, const std::string& description);
    virtual ~ItemDescription() = default;

    virtual ItemFormat getType() const = 0;
    const std::string& getDescription() const;
    int getId() const;

private:
    int _id;
    std::string _description;
};

using ItemDescriptionVector = std::vector<ItemDescriptionPtr>;

} /* namespace artus */
