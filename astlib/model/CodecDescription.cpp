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
#include "Exception.h"

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

void CodecDescription::addUapItem(int frn, int itemId)
{
    auto item = getDataItemById(itemId);
    poco_assert(item);
    _uapItems[frn] = item;

}

} /* namespace astlib */
