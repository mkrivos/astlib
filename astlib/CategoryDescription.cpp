///
/// \package astlib
/// \file CategoryDescription.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 1Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "CategoryDescription.h"

namespace astlib
{

CategoryDescription::CategoryDescription()
{
}

CategoryDescription::~CategoryDescription()
{
}

int CategoryDescription::getCategory() const
{
    return _category;
}

void CategoryDescription::setCategory(int category)
{
    _category = category;
}

const std::string& CategoryDescription::getDescription() const
{
    return _description;
}

void CategoryDescription::setDescription(const std::string& description)
{
    _description = description;
}

const std::string& CategoryDescription::getEdition() const
{
    return _edition;
}

void CategoryDescription::setEdition(const std::string& edition)
{
    _edition = edition;
}

const std::string& CategoryDescription::getFamily() const
{
    return _family;
}

void CategoryDescription::setFamily(const std::string& family)
{
    _family = family;
}

std::string CategoryDescription::toString() const
{
    return getFamily() + "-" + std::to_string(getCategory()) + "-" + getEdition();
}

} /* namespace astlib */
