///
/// \package astlib
/// \file GeneratedTypes.h
/// \brief Tento subor needitovat, bol automaticky generovany programom codegen!
///
/// \author marian.krivos@r-sys.sk
/// \date 26.4.2017
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#ifndef _GeneratedTypes_H_
#define _GeneratedTypes_H_

#include "rsys/Enumerator.h"
#include "Astlib.h"
#include <string>

namespace astlib {

#pragma pack(1) 
class ASTLIB_API ItemFormat
  : public rsys::Enumerator
{ 
public:
    typedef Poco::UInt32 ValueType;

    static const ValueType Fixed = 0;
    static const ValueType Explicit = 1;
    static const ValueType Variable = 2;
    static const ValueType Repetitive = 3;
    static const ValueType Compound = 4;

    ItemFormat(ValueType v = 0) : _value(v) {}

    ItemFormat(const std::string& v) : _value(0) { fromString(v); }

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

    bool operator != (ItemFormat right) const { return toValue() != right.toValue(); }
    bool operator == (ItemFormat right) const { return toValue() == right.toValue(); }

private:
    static std::vector<std::string> definitionList;

    ValueType _value;
};
#pragma pack() 

#pragma pack(1) 
class ASTLIB_API AsterixFamily
  : public rsys::Enumerator
{ 
public:
    typedef Poco::UInt32 ValueType;

    static const ValueType Eurocontrol = 0;
    static const ValueType Era = 1;
    static const ValueType Thales = 2;

    AsterixFamily(ValueType v = 0) : _value(v) {}

    AsterixFamily(const std::string& v) : _value(0) { fromString(v); }

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

    bool operator != (AsterixFamily right) const { return toValue() != right.toValue(); }
    bool operator == (AsterixFamily right) const { return toValue() == right.toValue(); }

private:
    static std::vector<std::string> definitionList;

    ValueType _value;
};
#pragma pack() 

#pragma pack(1) 
class ASTLIB_API Rule
  : public rsys::Enumerator
{ 
public:
    typedef Poco::UInt32 ValueType;

    static const ValueType Optional = 0;
    static const ValueType Mandatory = 1;

    Rule(ValueType v = 0) : _value(v) {}

    Rule(const std::string& v) : _value(0) { fromString(v); }

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

    bool operator != (Rule right) const { return toValue() != right.toValue(); }
    bool operator == (Rule right) const { return toValue() == right.toValue(); }

private:
    static std::vector<std::string> definitionList;

    ValueType _value;
};
#pragma pack() 

#pragma pack(1) 
class ASTLIB_API Units
  : public rsys::Enumerator
{ 
public:
    typedef Poco::UInt32 ValueType;

    static const ValueType None = 0;
    static const ValueType M = 1;
    static const ValueType M_S = 2;
    static const ValueType M_S2 = 3;
    static const ValueType FT = 4;
    static const ValueType NM = 5;
    static const ValueType NM_S = 6;
    static const ValueType FL = 7;
    static const ValueType DEG = 8;
    static const ValueType KT = 9;
    static const ValueType S = 10;
    static const ValueType NS = 11;
    static const ValueType PERCENT = 12;

    Units(ValueType v = 0) : _value(v) {}

    Units(const std::string& v) : _value(0) { fromString(v); }

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

    bool operator != (Units right) const { return toValue() != right.toValue(); }
    bool operator == (Units right) const { return toValue() == right.toValue(); }

private:
    static std::vector<std::string> definitionList;

    ValueType _value;
};
#pragma pack() 

#pragma pack(1) 
class ASTLIB_API Encoding
  : public rsys::Enumerator
{ 
public:
    typedef Poco::UInt32 ValueType;

    static const ValueType Signed = 0;
    static const ValueType Unsigned = 1;
    static const ValueType SixBitsChar = 2;
    static const ValueType Octal = 3;
    static const ValueType Ascii = 4;
    static const ValueType Hex = 5;

    Encoding(ValueType v = 0) : _value(v) {}

    Encoding(const std::string& v) : _value(0) { fromString(v); }

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

    bool operator != (Encoding right) const { return toValue() != right.toValue(); }
    bool operator == (Encoding right) const { return toValue() == right.toValue(); }

private:
    static std::vector<std::string> definitionList;

    ValueType _value;
};
#pragma pack() 

#pragma pack(1) 
class ASTLIB_API PrimitiveType
  : public rsys::Enumerator
{ 
public:
    typedef Poco::UInt32 ValueType;

    static const ValueType Unknown = 0;
    static const ValueType Boolean = 1;
    static const ValueType Integer = 2;
    static const ValueType Unsigned = 3;
    static const ValueType Real = 4;
    static const ValueType String = 5;

    PrimitiveType(ValueType v = 0) : _value(v) {}

    PrimitiveType(const std::string& v) : _value(0) { fromString(v); }

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

    bool operator != (PrimitiveType right) const { return toValue() != right.toValue(); }
    bool operator == (PrimitiveType right) const { return toValue() == right.toValue(); }

private:
    static std::vector<std::string> definitionList;

    ValueType _value;
};
#pragma pack() 

}
#endif
