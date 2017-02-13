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
#include "astlib/PrimitiveItem.h"

#include <Poco/Dynamic/Var.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

namespace astlib
{

/**
 * Contains complete description for one concrete asterix category version.
 * Description has table with all data items plus User Asterix Profile table.
 * With iterations over this items we can interpret all decode/encode rules.
 */
class CodecDescription
{
public:
    struct UapItem
    {
        UapItem() {}
        UapItem(ItemDescriptionPtr item, bool mandatory) :
            item(item),
            mandatory(mandatory)
        {
        }

        ItemDescriptionPtr item;
        bool mandatory = false;
    };
    using Parameters = std::unordered_map<std::string, Poco::Dynamic::Var>;
    using ItemDescriptionTable = std::unordered_map<int, ItemDescriptionPtr>;
    using UapItems = std::map<int, UapItem>;
    using Dictionary = std::map<std::string, PrimitiveItem>;

    CodecDescription();
    ~CodecDescription();

    void addCategoryDescription(const CategoryDescription& categoryDescription);
    const CategoryDescription& getCategoryDescription() const;

    void addParameter(const std::string& name, const Poco::Dynamic::Var& value);
    const Poco::Dynamic::Var& getParameter(const std::string& name) const;

    void addDataItem(ItemDescriptionPtr item);
    ItemDescriptionPtr getDataItemById(int id);
    const ItemDescriptionTable& enumerateDataItems() const;

    void addUapItem(int frn, int itemId, bool mandatory);
    const UapItems& enumerateUapItems() const;

    void addPrimitiveItem(const std::string& name, const PrimitiveItem& item);
    const Dictionary& getDictionary() const;

private:
    CategoryDescription _categoryDescription;
    ItemDescriptionTable _dataItems;
    Parameters _parameters;
    UapItems _uapItems;
    Dictionary _itemDictionary;
};

using CodecDescriptionPtr = std::shared_ptr<CodecDescription>;
using CodecDescriptionVector = std::vector<CodecDescriptionPtr>;

} /* namespace astlib */

