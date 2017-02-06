///
/// \package astlib
/// \file CategoryDescription.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 1Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include <string>

#include "astlib/GeneratedTypes.h"
#include "astlib/AsterixVersion.h"

namespace astlib
{

class CategoryDescription
{
public:
    CategoryDescription();
    ~CategoryDescription();

    int getCategory() const;
    void setCategory(int category);

    const std::string& getDescription() const;
    void setDescription(const std::string& description);

    AsterixVersion getEdition() const;
    void setEdition(const std::string& edition);

    AsterixFamily getFamily() const;
    void setFamily(AsterixFamily family);

    std::string toString() const;

private:
    int _category;
    AsterixVersion _edition;
    AsterixFamily _family;
    std::string _description;
};

} /* namespace astlib */

