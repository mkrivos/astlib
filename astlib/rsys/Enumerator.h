///
/// \package rsys
/// \file Enumerator.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date Aug 6, 2008 - 2:21:17 PM
///
/// (C) Copyright 2008 R-SYS,s.r.o
/// All rights reserved.
///

#ifndef RSYSENUMERATOR_H_
#define RSYSENUMERATOR_H_

#include <Poco/SharedPtr.h>
#include <Poco/Types.h>
#include <string>
#include <vector>

namespace rsys
{

/**
 * Rozhranie ktore musia podporovat vsetky generovane enum a bitset.
 */
class Enumerator
{
public:
    virtual ~Enumerator() = default;

    //! @return textova reprezentacia hodnoty objektu
    virtual std::string toString() const = 0;

    //! nastav hodnotu objektu podla textovej representacie
    virtual void fromString(const std::string &value) = 0;

    //! @return hodnotu ako integralny typ
    virtual Poco::UInt64 toValue() const = 0;

    //! zvaliduj obsah objektu
    virtual bool validate() const { return true; }

    //! \return iteracny objekt pre enumeraciu zaznamov objektu
    virtual const std::vector<std::string>& enumerate() const = 0;
};

typedef Poco::SharedPtr<Enumerator> EnumeratorPtr;

}

#endif /* ENUMERATOR_H_ */
