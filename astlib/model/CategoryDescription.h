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

    const std::string& getEdition() const;
    void setEdition(const std::string& edition);

    const std::string& getFamily() const;
    void setFamily(const std::string& family);

    std::string toString() const;

private:
    int _category;
    std::string _edition;
    std::string _family;
    std::string _description;
};

} /* namespace astlib */

