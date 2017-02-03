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
const ItemFormat::ValueType ItemFormat::Fixed;
const ItemFormat::ValueType ItemFormat::Explicit;
const ItemFormat::ValueType ItemFormat::Variable;
const ItemFormat::ValueType ItemFormat::Repetitive;
const ItemFormat::ValueType ItemFormat::Compound;
#endif

std::vector<std::string> ItemFormat::definitionList = 
{
    "Fixed",
    "Explicit",
    "Variable",
    "Repetitive",
    "Compound",
};

std::string ItemFormat::toString() const
{
    switch(_value)
    {
        case Fixed: return "Fixed";
        case Explicit: return "Explicit";
        case Variable: return "Variable";
        case Repetitive: return "Repetitive";
        case Compound: return "Compound";
    }

    return "ItemFormat::UndefinedValue";
}

void ItemFormat::fromString(const std::string& str)
{
    _value = 0;
    if (str ==  "Fixed")  { _value = Fixed; return; }
    if (str ==  "Explicit")  { _value = Explicit; return; }
    if (str ==  "Variable")  { _value = Variable; return; }
    if (str ==  "Repetitive")  { _value = Repetitive; return; }
    if (str ==  "Compound")  { _value = Compound; return; }
}

bool ItemFormat::validate() const
{
    switch(_value)
    {
        case Fixed:
        case Explicit:
        case Variable:
        case Repetitive:
        case Compound:
            return true;
    }

    return false;
}

const std::vector<std::string>& ItemFormat::enumerate() const
{
    return definitionList;
}

#ifndef _MSC_VER
const AsterixFamily::ValueType AsterixFamily::Eurocontrol;
const AsterixFamily::ValueType AsterixFamily::Era;
const AsterixFamily::ValueType AsterixFamily::Thales;
#endif

std::vector<std::string> AsterixFamily::definitionList = 
{
    "Eurocontrol",
    "Era",
    "Thales",
};

std::string AsterixFamily::toString() const
{
    switch(_value)
    {
        case Eurocontrol: return "Eurocontrol";
        case Era: return "Era";
        case Thales: return "Thales";
    }

    return "AsterixFamily::UndefinedValue";
}

void AsterixFamily::fromString(const std::string& str)
{
    _value = 0;
    if (str ==  "Eurocontrol")  { _value = Eurocontrol; return; }
    if (str ==  "Era")  { _value = Era; return; }
    if (str ==  "Thales")  { _value = Thales; return; }
}

bool AsterixFamily::validate() const
{
    switch(_value)
    {
        case Eurocontrol:
        case Era:
        case Thales:
            return true;
    }

    return false;
}

const std::vector<std::string>& AsterixFamily::enumerate() const
{
    return definitionList;
}

#ifndef _MSC_VER
const Rule::ValueType Rule::Optional;
const Rule::ValueType Rule::Mandatory;
#endif

std::vector<std::string> Rule::definitionList = 
{
    "Optional",
    "Mandatory",
};

std::string Rule::toString() const
{
    switch(_value)
    {
        case Optional: return "Optional";
        case Mandatory: return "Mandatory";
    }

    return "Rule::UndefinedValue";
}

void Rule::fromString(const std::string& str)
{
    _value = 0;
    if (str ==  "Optional")  { _value = Optional; return; }
    if (str ==  "Mandatory")  { _value = Mandatory; return; }
}

bool Rule::validate() const
{
    switch(_value)
    {
        case Optional:
        case Mandatory:
            return true;
    }

    return false;
}

const std::vector<std::string>& Rule::enumerate() const
{
    return definitionList;
}

#ifndef _MSC_VER
const Encoding::ValueType Encoding::Signed;
const Encoding::ValueType Encoding::Unsigned;
const Encoding::ValueType Encoding::SixBitsCHar;
const Encoding::ValueType Encoding::Octal;
const Encoding::ValueType Encoding::Ascii;
const Encoding::ValueType Encoding::Hex;
#endif

std::vector<std::string> Encoding::definitionList = 
{
    "Signed",
    "Unsigned",
    "SixBitsCHar",
    "Octal",
    "Ascii",
    "Hex",
};

std::string Encoding::toString() const
{
    switch(_value)
    {
        case Signed: return "Signed";
        case Unsigned: return "Unsigned";
        case SixBitsCHar: return "SixBitsCHar";
        case Octal: return "Octal";
        case Ascii: return "Ascii";
        case Hex: return "Hex";
    }

    return "Encoding::UndefinedValue";
}

void Encoding::fromString(const std::string& str)
{
    _value = 0;
    if (str ==  "Signed")  { _value = Signed; return; }
    if (str ==  "Unsigned")  { _value = Unsigned; return; }
    if (str ==  "SixBitsCHar")  { _value = SixBitsCHar; return; }
    if (str ==  "Octal")  { _value = Octal; return; }
    if (str ==  "Ascii")  { _value = Ascii; return; }
    if (str ==  "Hex")  { _value = Hex; return; }
}

bool Encoding::validate() const
{
    switch(_value)
    {
        case Signed:
        case Unsigned:
        case SixBitsCHar:
        case Octal:
        case Ascii:
        case Hex:
            return true;
    }

    return false;
}

const std::vector<std::string>& Encoding::enumerate() const
{
    return definitionList;
}

}
