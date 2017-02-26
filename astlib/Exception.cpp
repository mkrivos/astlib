///
/// \package astlib
/// \file Exception.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 31Jan.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "Exception.h"

namespace astlib
{

Exception::Exception(const std::string& msg) :
    _message(msg)
{
}

Exception::~Exception()
{
}

const std::string& Exception::displayText() const
{
    return _message;
}

} /* namespace astlib */
