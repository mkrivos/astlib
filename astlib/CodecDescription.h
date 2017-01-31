///
/// \package astlib
/// \file CodecDescription.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
/// See LICENCE file in project root directory
///

#pragma once

#include <memory>

namespace astlib
{

class CodecDescription
{
public:
    CodecDescription();
    ~CodecDescription();
};

using CodecDescriptionPtr = std::shared_ptr<CodecDescription>;
} /* namespace astlib */

