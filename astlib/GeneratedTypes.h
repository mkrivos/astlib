///
/// \package astlib
/// \file GeneratedTypes.h
/// \brief Tento subor needitovat, bol automaticky generovany programom codegen!
///
/// \author marian.krivos@r-sys.sk
/// \date 2.2.2017
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#ifndef _GeneratedTypes_H_
#define _GeneratedTypes_H_

#include "rsys/Enumerator.h"
#include <string>
#include <iosfwd>
#include <iomanip>

typedef unsigned char Byte;


namespace astlib {

#pragma pack(1) 
class ItemType
  : public rsys::Enumerator
{ 
public:
    typedef Poco::UInt32 ValueType;

    static const ValueType Fixed = 0;
    static const ValueType Variable = 1;
    static const ValueType Repetitive = 2;
    static const ValueType Compound = 3;

    ItemType(ValueType v = 0) : _value(v) {}

    ItemType(const std::string& v) : _value(0) { fromString(v); }

    //! @return textova reprezentacia hodnoty objektu
    std::string toString() const;

    //! nastav hodnotu objektu podla textovej representacie
    void fromString(const std::string &value);

    //! @return hodnotu ako integralny typ
    Poco::UInt64 toValue() const { return _value; }

    //! \return iteracny objekt pre enumeraciu zaznamov objektu
    const std::vector<std::string>& enumerate() const;

    //! validuj objekt na korektnu hodnotu, return true ak je objekt validny, inak false
    bool validate() const;

    //! nastav hodnotu objektu z integralnej reprezentatacie
    void fromValue(ValueType val) { _value = val; }

    bool operator != (ItemType right) const { return toValue() != right.toValue(); }
    bool operator == (ItemType right) const { return toValue() == right.toValue(); }

private:
    static std::vector<std::string> definitionList;

    ValueType _value;
};
#pragma pack() 

}
#endif
