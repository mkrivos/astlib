///
/// \package astlib
/// \file FspecGenerator.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 20Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/ByteUtils.h"
#include <vector>


namespace astlib
{

class FspecGenerator
{
public:
    FspecGenerator();
    ~FspecGenerator();

    void addItem();
    void skipItem();
    void skipItems(int count);

    size_t size() const;
    const Byte* data() const;

private:
    std::vector<Byte> _fspec;
    int _byteMask = 0x100;
};

} /* namespace astlib */

