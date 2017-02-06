///
/// \package astlib
/// \file Exception.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include <string>
#include <exception>

namespace astlib
{

class Exception:
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

