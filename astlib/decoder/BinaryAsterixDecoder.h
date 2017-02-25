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

#include "astlib/CodecPolicy.h"
#include "ValueDecoder.h"
#include "astlib/model/CodecDescription.h"
#include "astlib/model/Fixed.h"
#include "astlib/ByteUtils.h"

namespace astlib
{

/**
 * Implements asterix binary data dekoder by interpreting CodecDescription and pushing decoded item to user ValueDecoder implementation.
 */
class BinaryAsterixDecoder
{
public:
    static constexpr int MAX_PACKET_SIZE = 8192;

    BinaryAsterixDecoder(CodecPolicy policy = CodecPolicy());
    ~BinaryAsterixDecoder();

    /**
     * Decodes binary asterix data from buffer with size.
     * @param codec formal description of concrete asterix category
     * @param valueDecoder callback object for pushing decoded items to user code
     * @param buf asterix data buffer, first byte is byte containing category number
     * @param bytes the effective size of buffer data
     */
    void decode(const CodecDescription& codec, ValueDecoder& valueDecoder, const Byte buf[], size_t bytes);

private:
    // Integer sizes are used instead of unsigned types for underflow/overflow detection
    int decodeRecord(const CodecDescription& codec, ValueDecoder& valueDecoder, const Byte buf[]);
    int decodeFixed(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte ptr[]);
    int decodeVariable(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte ptr[]);
    int decodeRepetitive(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte ptr[]);
    int decodeCompound(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte ptr[]);

    void decodeBitset(const ItemDescription& uapItem, const Fixed& fixed, const Byte localPtr[], ValueDecoder& valueDecoder, int index, int arraySize);

    CodecPolicy _policy;
    int _depth = 0;
};

} /* namespace astlib */

