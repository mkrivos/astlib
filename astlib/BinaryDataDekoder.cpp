///
/// \package astlib
/// \file BinaryDataDekoder.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 6Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "BinaryDataDekoder.h"
#include "Exception.h"
#include <Poco/ByteOrder.h>

namespace astlib
{

BinaryDataDekoder::BinaryDataDekoder()
{
}

BinaryDataDekoder::~BinaryDataDekoder()
{
}

void BinaryDataDekoder::decode(const CodecDescription& codec, const Byte buf[], size_t bytes)
{
    if (bytes < 6)
    {
        throw Exception("Too short message in BinaryDataDekoder::decode()");
    }

    const unsigned short *sizePtr;
    const Byte *fspecPtr;
    unsigned index = 1;

    sizePtr = (unsigned short *)(buf+index);
    // TODO: risit endian z codec
    short size = Poco::ByteOrder::fromNetwork(*sizePtr);
    index += 2;

    size -= index;

    if (size < 2 || size > 2048)
    {
        throw Exception("Bad size of subpacket in BinaryDataDekoder::decode()");
    }

    while(1)
    {
        fspecPtr = (Byte *)buf+index;

        if (size == 0)
            break;

        int len = decodeSubMessage(fspecPtr, size);

        // Chyba, treba vyskocit inak bude nekonecna slucka
        if (len <= 0)
            break;

        index += len;
        size -= len;

        if (index > bytes)
            throw Exception("BinaryDataDekoder::decode(): buffer overflow - codec eats " + std::to_string(index-bytes) + " more bytes");

        if (index >= bytes)
            break;
    }
}

int BinaryDataDekoder::decodeSubMessage(const CodecDescription& codec, const Byte buf[], size_t size)
{
    return 0;
}

} /* namespace astlib */
