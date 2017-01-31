///
/// \package astlib
/// \file Exception.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
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

const std::string& Exception::displayMessage() const
{
    return _message;
}

} /* namespace astlib */
