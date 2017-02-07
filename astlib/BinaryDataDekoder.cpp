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
#include "model/FixedItemDescription.h"
#include "model/VariableItemDescription.h"
#include "model/RepetitiveItemDescription.h"

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

void BinaryDataDekoder::decode(const CodecDescription& codec, ValueDecoder& valueDecoder, const Byte buf[], size_t bytes)
{
    if (bytes < 6)
    {
        throw Exception("Too short message in BinaryDataDekoder::decode()");
    }

    const unsigned short *sizePtr;
    const Byte *fspecPtr;
    unsigned index = 1;

    sizePtr = (unsigned short *)(buf+index);
    // TODO: brat endian z codec
    int size = Poco::ByteOrder::fromNetwork(*sizePtr);
    index += 2;

    size -= index;

    if (size < 2 || size > MAX_PACKET_SIZE)
    {
        throw Exception("Bad size of subpacket in BinaryDataDekoder::decode()");
    }

    while(1)
    {
        fspecPtr = (Byte *)buf+index;

        if (size == 0)
            break;

        int len = decodeSubRecord(codec, valueDecoder, fspecPtr);

        // Chyba, treba vyskocit inak bude nekonecna slucka
        if (len <= 0)
            throw Exception("BinaryDataDekoder::decode(): buffer underflow");

        index += len;
        size -= len;

        if (index > bytes)
            throw Exception("BinaryDataDekoder::decode(): buffer overflow - codec eats " + std::to_string(index-bytes) + " more bytes");

        //if (index < bytes) throw Exception("BinaryDataDekoder::decode(): buffer underflow - codec eats " + std::to_string(bytes-index) + " less bytes");

        if (index == bytes)
            break;
    }
}

void BinaryDataDekoder::decodeFixedItem(const Fixed& fixed, const Byte* localPtr, ValueDecoder& valueDecoder)
{
    const BitsDescriptionArray& bitsDescriptions = fixed.bitsDescriptions;
    Poco::UInt64 data = 0;
    for (int i = 0; i < fixed.length; i++)
    {
        data <<= 8;
        data |= localPtr[i];
    }
    for (const BitsDescription& bits : bitsDescriptions)
    {
        if (bits.bit != -1)
        {
            Poco::UInt64 value = ((data >> (bits.bit - 1)) & 1);
            valueDecoder.decode(value, bits);
        }
        else
        {
            int from = bits.from;
            int to = bits.to;
            if (from < to)
                std::swap(from, to);
            
            int mask = (1 << (from - to + 1)) - 1;
            Poco::UInt64 value = ((data >> (to - 1)) & mask);
            valueDecoder.decode(value, bits);
        }
    }
}

int BinaryDataDekoder::decodeSubRecord(const CodecDescription& codec, ValueDecoder& valueDecoder, const Byte fspecPtr[])
{
    const Byte* startPtr = fspecPtr;
    size_t fspecLen = ByteUtils::calculateFspec(fspecPtr);

    if (fspecPtr[0] == 0)
        throw Exception("Bad FSPEC[0] value for decoded message in AsterixCategory::decodeMessageERA()");

    const Byte *localPtr = fspecPtr + fspecLen;
    int fspecMask = 0x80;
    int currentFspecBit = 0;

    // Loop for all fspec bits
    const CodecDescription::UapItems uapItems = codec.enumerateUapItems();

    valueDecoder.begin();

    for (size_t i = 0; i < fspecLen; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            bool bitPresent = (fspecMask & *fspecPtr);  // priznak pritomnosti aktualne testovaneho FSPEC bitu
            int decodedByteCount = 0;

            if (fspecMask & FX_BIT)
            {
                fspecMask = 0x80;
                // Sme v prechode na dalsi FSPEC bajt
                if (bitPresent == false)
                {
                    // Definitivne koncime
                    break;
                }

                fspecPtr++;
                currentFspecBit++;
                continue;
            }

            auto iterator = uapItems.find(currentFspecBit);
            if (iterator == uapItems.end())
                throw Exception("Undefined Data Item for bit " + std::to_string(currentFspecBit));

            const ItemDescription& uapItem = *iterator->second.item;
            bool mandatory = iterator->second.mandatory;

            if (bitPresent)
            {
                valueDecoder.item(uapItem);

                switch(uapItem.getType().toValue())
                {
                    case ItemFormat::Fixed:
                    {
                        const FixedItemDescription& fixedItem = static_cast<const FixedItemDescription&>(uapItem);
                        const Fixed& fixed = fixedItem.getFixed();
                        decodeFixedItem(fixed, localPtr, valueDecoder);
                        decodedByteCount += fixed.length;
                    }
                    break;

                    case ItemFormat::Variable:
                    {
                        const VariableItemDescription& varItem = static_cast<const VariableItemDescription&>(uapItem);
                        const FixedVector& fixedVector = varItem.getFixedVector();
                        auto ptr = localPtr;
                        for(const Fixed& fixed: fixedVector)
                        {
                            decodeFixedItem(fixed, ptr, valueDecoder);
                            decodedByteCount += fixed.length;
                            if ((ptr[0] & FX_BIT) == 0)
                                break;
                            ptr += fixed.length;
                        }
                    }
                    break;

                    case ItemFormat::Repetitive:
                    {
                        const RepetitiveItemDescription& varItem = static_cast<const RepetitiveItemDescription&>(uapItem);
                        const FixedVector& fixedVector = varItem.getFixedVector();
                        int counter = *localPtr;
                        decodedByteCount += 1;
                        auto ptr = localPtr+1;

                        for(int j = 0; j < counter; j++)
                        {
                            for(const Fixed& fixed: fixedVector)
                            {
                                decodeFixedItem(fixed, ptr, valueDecoder);
                                decodedByteCount += fixed.length;
                                ptr += fixed.length;
                            }
                        }
                    }
                    break;
                }
            }
            else if (mandatory)
            {
                // TODO: nepritomna ale povinna polozka ...
            }

            localPtr += decodedByteCount;
            currentFspecBit++;
            fspecMask >>= 1;
        }
    }

    valueDecoder.end();

    return localPtr-startPtr;
}

} /* namespace astlib */
