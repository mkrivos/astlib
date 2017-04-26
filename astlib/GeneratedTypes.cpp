///
/// \package astlib
/// \file GeneratedTypes.cpp
/// \brief Tento subor needitovat, bol automaticky generovany programom codegen!
///
/// \author marian.krivos@r-sys.sk
/// \date 26.4.2017
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
const Units::ValueType Units::None;
const Units::ValueType Units::M;
const Units::ValueType Units::M_S;
const Units::ValueType Units::M_S2;
const Units::ValueType Units::FT;
const Units::ValueType Units::NM;
const Units::ValueType Units::NM_S;
const Units::ValueType Units::FL;
const Units::ValueType Units::DEG;
const Units::ValueType Units::KT;
const Units::ValueType Units::S;
const Units::ValueType Units::NS;
const Units::ValueType Units::PERCENT;
#endif

std::vector<std::string> Units::definitionList = 
{
    "None",
    "M",
    "M_S",
    "M_S2",
    "FT",
    "NM",
    "NM_S",
    "FL",
    "DEG",
    "KT",
    "S",
    "NS",
    "PERCENT",
};

std::string Units::toString() const
{
    switch(_value)
    {
        case None: return "None";
        case M: return "M";
        case M_S: return "M_S";
        case M_S2: return "M_S2";
        case FT: return "FT";
        case NM: return "NM";
        case NM_S: return "NM_S";
        case FL: return "FL";
        case DEG: return "DEG";
        case KT: return "KT";
        case S: return "S";
        case NS: return "NS";
        case PERCENT: return "PERCENT";
    }

    return "Units::UndefinedValue";
}

void Units::fromString(const std::string& str)
{
    _value = 0;
    if (str ==  "None")  { _value = None; return; }
    if (str ==  "M")  { _value = M; return; }
    if (str ==  "M_S")  { _value = M_S; return; }
    if (str ==  "M_S2")  { _value = M_S2; return; }
    if (str ==  "FT")  { _value = FT; return; }
    if (str ==  "NM")  { _value = NM; return; }
    if (str ==  "NM_S")  { _value = NM_S; return; }
    if (str ==  "FL")  { _value = FL; return; }
    if (str ==  "DEG")  { _value = DEG; return; }
    if (str ==  "KT")  { _value = KT; return; }
    if (str ==  "S")  { _value = S; return; }
    if (str ==  "NS")  { _value = NS; return; }
    if (str ==  "PERCENT")  { _value = PERCENT; return; }
}

bool Units::validate() const
{
    switch(_value)
    {
        case None:
        case M:
        case M_S:
        case M_S2:
        case FT:
        case NM:
        case NM_S:
        case FL:
        case DEG:
        case KT:
        case S:
        case NS:
        case PERCENT:
            return true;
    }

    return false;
}

const std::vector<std::string>& Units::enumerate() const
{
    return definitionList;
}

#ifndef _MSC_VER
const Encoding::ValueType Encoding::Signed;
const Encoding::ValueType Encoding::Unsigned;
const Encoding::ValueType Encoding::SixBitsChar;
const Encoding::ValueType Encoding::Octal;
const Encoding::ValueType Encoding::Ascii;
const Encoding::ValueType Encoding::Hex;
#endif

std::vector<std::string> Encoding::definitionList = 
{
    "Signed",
    "Unsigned",
    "SixBitsChar",
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
        case SixBitsChar: return "SixBitsChar";
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
    if (str ==  "SixBitsChar")  { _value = SixBitsChar; return; }
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
        case SixBitsChar:
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

#ifndef _MSC_VER
const PrimitiveType::ValueType PrimitiveType::Unknown;
const PrimitiveType::ValueType PrimitiveType::Boolean;
const PrimitiveType::ValueType PrimitiveType::Integer;
const PrimitiveType::ValueType PrimitiveType::Unsigned;
const PrimitiveType::ValueType PrimitiveType::Real;
const PrimitiveType::ValueType PrimitiveType::String;
#endif

std::vector<std::string> PrimitiveType::definitionList = 
{
    "Unknown",
    "Boolean",
    "Integer",
    "Unsigned",
    "Real",
    "String",
};

std::string PrimitiveType::toString() const
{
    switch(_value)
    {
        case Unknown: return "Unknown";
        case Boolean: return "Boolean";
        case Integer: return "Integer";
        case Unsigned: return "Unsigned";
        case Real: return "Real";
        case String: return "String";
    }

    return "PrimitiveType::UndefinedValue";
}

void PrimitiveType::fromString(const std::string& str)
{
    _value = 0;
    if (str ==  "Unknown")  { _value = Unknown; return; }
    if (str ==  "Boolean")  { _value = Boolean; return; }
    if (str ==  "Integer")  { _value = Integer; return; }
    if (str ==  "Unsigned")  { _value = Unsigned; return; }
    if (str ==  "Real")  { _value = Real; return; }
    if (str ==  "String")  { _value = String; return; }
}

bool PrimitiveType::validate() const
{
    switch(_value)
    {
        case Unknown:
        case Boolean:
        case Integer:
        case Unsigned:
        case Real:
        case String:
            return true;
    }

    return false;
}

const std::vector<std::string>& PrimitiveType::enumerate() const
{
    return definitionList;
}

}
