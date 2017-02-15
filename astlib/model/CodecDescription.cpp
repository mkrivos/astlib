///
/// \package astlib
/// \file CodecDescription.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
/// See LICENCE file in project root directory
///

#include "CodecDescription.h"
#include "astlib/Exception.h"
#include <iostream>

namespace astlib
{

CodecDescription::CodecDescription()
{
}

CodecDescription::~CodecDescription()
{
}

void CodecDescription::addCategoryDescription(const CategoryDescription& categoryDescription)
{
    _categoryDescription = categoryDescription;
}

const CategoryDescription& CodecDescription::getCategoryDescription() const
{
    return _categoryDescription;
}

void CodecDescription::addParameter(const std::string& name, const Poco::Dynamic::Var& value)
{
    _parameters[name] = value;
}

const Poco::Dynamic::Var& CodecDescription::getParameter(const std::string& name) const
{
    auto iterator = _parameters.find(name);

    if (iterator != _parameters.end())
    {
        return iterator->second;
    }

    throw Exception("CodecDescription::getParameter(): " + name);
}

void CodecDescription::addDataItem(ItemDescriptionPtr item)
{
    _dataItems[item->getId()] = item;
}

ItemDescriptionPtr CodecDescription::getDataItemById(int id)
{
    return _dataItems[id];
}

const CodecDescription::ItemDescriptionTable& CodecDescription::enumerateDataItems() const
{
    return _dataItems;
}

void CodecDescription::addUapItem(int frn, int itemId, bool mandatory)
{
    auto item = getDataItemById(itemId);
    _uapItems[frn] = UapItem{ item, mandatory };
}

const CodecDescription::UapItems& CodecDescription::enumerateUapItems() const
{
    return _uapItems;
}

const CodecDescription::Dictionary& CodecDescription::getDictionary() const
{
    return _itemDictionary;
}


void CodecDescription::addPrimitiveItem(const std::string& name, const PrimitiveItem& item)
{
    auto iterator = _itemDictionary.find(name);

    if (iterator != _itemDictionary.end())
    {
        //std::cerr << "Cat " << _categoryDescription.getCategory() << " redefinition: " << name << std::endl;
    }

    _itemDictionary[name] = item;
}

} /* namespace astlib */
