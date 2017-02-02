///
/// \package astlib
/// \file GeneratedTypes.cpp
/// \brief Tento subor needitovat, bol automaticky generovany programom codegen!
///
/// \author marian.krivos@r-sys.sk
/// \date 2.2.2017
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "GeneratedTypes.h"
#include <Poco/NumberFormatter.h>
#include <sstream>
#include <cassert>

#include <Poco/Exception.h>

namespace astlib {

#ifndef _MSC_VER
const ItemType::ValueType ItemType::Fixed;
const ItemType::ValueType ItemType::Variable;
const ItemType::ValueType ItemType::Repetitive;
const ItemType::ValueType ItemType::Compound;
#endif

std::vector<std::string> ItemType::definitionList = 
{
    "Fixed",
    "Variable",
    "Repetitive",
    "Compound",
};

std::string ItemType::toString() const
{
    switch(_value)
    {
        case Fixed: return "Fixed";
        case Variable: return "Variable";
        case Repetitive: return "Repetitive";
        case Compound: return "Compound";
    }

    return "ItemType::UndefinedValue";
}

void ItemType::fromString(const std::string& str)
{
    _value = 0;
    if (str ==  "Fixed")  { _value = Fixed; return; }
    if (str ==  "Variable")  { _value = Variable; return; }
    if (str ==  "Repetitive")  { _value = Repetitive; return; }
    if (str ==  "Compound")  { _value = Compound; return; }
}

bool ItemType::validate() const
{
    switch(_value)
    {
        case Fixed:
        case Variable:
        case Repetitive:
        case Compound:
            return true;
    }

    return false;
}

const std::vector<std::string>& ItemType::enumerate() const
{
    return definitionList;
}

}
