///
/// \package astlib
/// \file ModelIterator.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 6Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

namespace astlib
{

class ModelIterator
{
public:
    ModelIterator(const CodecDescription& model);
    virtual ~ModelIterator();
};

} /* namespace astlib */

