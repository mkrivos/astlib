///
/// \package astlib
/// \file BinaryDataDekoder.h
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 6Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "model/CodecDescription.h"

namespace astlib
{

using Byte = unsigned char;

class BinaryDataDekoder
{
public:
    BinaryDataDekoder();
    virtual ~BinaryDataDekoder();

    void decode(const CodecDescription& codec, const Byte buf[], size_t bytes);

private:
    int decodeSubMessage(const CodecDescription& codec, const Byte buf[], size_t size);
};

} /* namespace astlib */

