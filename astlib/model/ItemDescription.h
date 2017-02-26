///
/// \package astlib
/// \file ItemDescription.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 1. 2. 2017 - 18:45:34
///
/// (C) Copyright 2017 R-SYS,s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/GeneratedTypes.h"
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
    static const int FX = -1;
    static const int RE = -2;
    static const int SP = -3;
    static const int NONE = -4;

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
