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
#include "model/ValueDecoder.h"
#include "model/Fixed.h"
#include "ByteUtils.h"

namespace astlib
{

class BinaryDataDekoder
{
public:
    static constexpr size_t MAX_PACKET_SIZE = 8192;

    BinaryDataDekoder();
    virtual ~BinaryDataDekoder();

    void decode(const CodecDescription& codec, ValueDecoder& valueDecoder, const Byte buf[], size_t bytes);

private:
    // Integer sizes are used instead of unsigned types for underflow/overflow detection
    int decodeSubRecord(const CodecDescription& codec, ValueDecoder& valueDecoder, const Byte buf[]);
    int decodeFixed(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte ptr[]);
    int decodeVariable(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte ptr[]);
    int decodeRepetitive(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte ptr[]);
    void decodeFixedItem(const Fixed& fixed, const Byte* localPtr, ValueDecoder& valueDecoder);
};

} /* namespace astlib */

