///
/// \package astlib
/// \file PrimitiveItem.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 13Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "GeneratedTypes.h"

namespace astlib
{

class PrimitiveItem
{
public:
    PrimitiveItem();
    PrimitiveItem(const std::string& name, const std::string& description, PrimitiveType type, bool arrayType);
    virtual ~PrimitiveItem();

    const std::string& getName() const;
    const std::string& getDescription() const;
    bool isArray() const;
    PrimitiveType getType() const;

private:
    std::string _name;
    std::string _description;
    PrimitiveType _type = PrimitiveType::Unknown;
    bool _arrayType;
};

} /* namespace astlib */

