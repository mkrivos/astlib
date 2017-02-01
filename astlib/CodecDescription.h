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

#include <Poco/Dynamic/Var.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace astlib
{

class CodecDescription
{
public:
    using Parameters = std::unordered_map<std::string, Poco::Dynamic::Var>;

    CodecDescription();
    ~CodecDescription();

    void addCategoryDescription(const CategoryDescription& categoryDescription);
    const CategoryDescription& getCategoryDescription() const;

    void addParameter(const std::string& name, const Poco::Dynamic::Var& value);
    const Poco::Dynamic::Var& getParameter(const std::string& name) const;

private:
    CategoryDescription _categoryDescription;
    Parameters _parameters;
};

using CodecDescriptionPtr = std::shared_ptr<CodecDescription>;

} /* namespace astlib */

