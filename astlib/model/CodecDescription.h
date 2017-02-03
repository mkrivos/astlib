///
/// \package astlib
/// \file CodecDescription.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
/// See LICENCE file in project root directory
///

#pragma once

#include "CategoryDescription.h"
#include "ItemDescription.h"

#include <Poco/Dynamic/Var.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <map>

namespace astlib
{

class CodecDescription
{
public:
    using Parameters = std::unordered_map<std::string, Poco::Dynamic::Var>;
    using ItemDescriptionTable = std::unordered_map<int, ItemDescriptionPtr>;
    using UapItems = std::map<int, ItemDescriptionPtr>;

    CodecDescription();
    ~CodecDescription();

    void addCategoryDescription(const CategoryDescription& categoryDescription);
    const CategoryDescription& getCategoryDescription() const;

    void addParameter(const std::string& name, const Poco::Dynamic::Var& value);
    const Poco::Dynamic::Var& getParameter(const std::string& name) const;

    void addDataItem(ItemDescriptionPtr item);
    ItemDescriptionPtr getDataItemById(int id);

    void addUapItem(int frn, int itemId);

private:
    CategoryDescription _categoryDescription;
    ItemDescriptionTable _dataItems;
    Parameters _parameters;
    UapItems _uapItems;
};

using CodecDescriptionPtr = std::shared_ptr<CodecDescription>;

} /* namespace astlib */

