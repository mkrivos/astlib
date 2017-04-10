///
/// \package astlib
/// \file Exception.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 31Jan.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "Astlib.h"

#include <string>
#include <exception>

namespace astlib
{

class ASTLIB_API Exception:
    public std::exception
{
public:
    Exception(const std::string& msg);
    virtual ~Exception();

    const std::string& displayText() const;
private:
    std::string _message;
};

} /* namespace astlib */

