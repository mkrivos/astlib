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

#include "BinaryAsterixDekoder.h"

#include "model/FixedItemDescription.h"
#include "model/VariableItemDescription.h"
#include "model/RepetitiveItemDescription.h"
#include "model/CompoundItemDescription.h"
#include "Exception.h"

#include <Poco/ByteOrder.h>
#include <iostream>

namespace astlib
{

BinaryAsterixDekoder::BinaryAsterixDekoder()
{
}

BinaryAsterixDekoder::~BinaryAsterixDekoder()
{
}

void BinaryAsterixDekoder::decode(const CodecDescription& codec, ValueDecoder& valueDecoder, const Byte buf[], size_t bytes)
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

        int len = decodeRecord(codec, valueDecoder, fspecPtr);

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

void BinaryAsterixDekoder::decodeBitset(const ItemDescription& uapItem, const Fixed& fixed, const Byte* localPtr, ValueDecoder& valueDecoder)
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
        ValueDecoder::Context context(uapItem, bits, _depth);

        if (context.width == 1)
        {
            // Send non FX bits only
            if (!bits.fx)
            {
                Poco::UInt64 value = ((data >> (bits.bit - 1)) & 1);
                valueDecoder.decode(value, context);
            }
        }
        else
        {
            Poco::UInt64 mask = (1ULL << bits.effectiveBitsWidth()) - 1;
            Poco::UInt64 value = ((data >> (bits.to - 1)) & mask);
            // depth, scope,
            valueDecoder.decode(value, context);
        }
    }
}

int BinaryAsterixDekoder::decodeRecord(const CodecDescription& codec, ValueDecoder& valueDecoder, const Byte fspecPtr[])
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
            if (iterator == uapItems.end() || (!iterator->second.item && bitPresent))
                throw Exception("Undefined Data Item for bit " + std::to_string(currentFspecBit));

            const ItemDescription& uapItem = *iterator->second.item;
            bool mandatory = iterator->second.mandatory;

            if (bitPresent)
            {
                valueDecoder.dataItem(uapItem);

                _depth++;

                switch(uapItem.getType().toValue())
                {
                    case ItemFormat::Fixed:
                        decodedByteCount += decodeFixed(uapItem, valueDecoder, localPtr);
                        break;

                    case ItemFormat::Variable:
                        decodedByteCount += decodeVariable(uapItem, valueDecoder, localPtr);
                        break;

                    case ItemFormat::Repetitive:
                        decodedByteCount += decodeRepetitive(uapItem, valueDecoder, localPtr);
                        break;

                    case ItemFormat::Compound:
                        decodedByteCount += decodeCompound(uapItem, valueDecoder, localPtr);
                        break;

                }

                --_depth;
            }
            else if (mandatory)
            {
                // TODO: nepritomna ale povinna polozka ...
            }

            std::cout << "  Item advance " << decodedByteCount << " bytes" << std::endl;
            localPtr += decodedByteCount;
            currentFspecBit++;
            fspecMask >>= 1;
        }
    }

    valueDecoder.end();

    return localPtr-startPtr;
}

int BinaryAsterixDekoder::decodeFixed(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte data[])
{
    const FixedItemDescription& fixedItem = static_cast<const FixedItemDescription&>(uapItem);
    const Fixed& fixed = fixedItem.getFixed();
    decodeBitset(uapItem, fixed, data, valueDecoder);
    return fixed.length;
}

int BinaryAsterixDekoder::decodeVariable(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte data[])
{
    const VariableItemDescription& varItem = static_cast<const VariableItemDescription&>(uapItem);
    const FixedVector& fixedVector = varItem.getFixedVector();
    auto ptr = data;
    int decodedByteCount = 0;

    for(;;)
    {
        Byte fspecBit;
        for(const Fixed& fixed: fixedVector)
        {
            fspecBit = (ptr[0] & FX_BIT);
            auto len = fixed.length;
            poco_assert(len == 1);
            decodeBitset(uapItem, fixed, ptr, valueDecoder);
            decodedByteCount += len;
            ptr += len;
            if (fspecBit == 0)
                break;
        }
        if (fspecBit == 0)
            break;
    }

    return decodedByteCount;
}

int BinaryAsterixDekoder::decodeRepetitive(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte data[])
{
    const RepetitiveItemDescription& varItem = static_cast<const RepetitiveItemDescription&>(uapItem);
    const FixedVector& fixedVector = varItem.getFixedVector();
    int decodedByteCount = 1;
    int counter = *data;
    auto ptr = data+1;

    valueDecoder.beginRepetitive(counter);

    for(int j = 0; j < counter; j++)
    {
        valueDecoder.repetitiveItem(j);
        for(const Fixed& fixed: fixedVector)
        {
            decodeBitset(uapItem, fixed, ptr, valueDecoder);
            decodedByteCount += fixed.length;
            ptr += fixed.length;
        }
    }

    valueDecoder.endRepetitive();

    return decodedByteCount;
}

int BinaryAsterixDekoder::decodeCompound(const ItemDescription& uapItem, ValueDecoder& valueDecoder, const Byte data[])
{
    const CompoundItemDescription& compoundItem = static_cast<const CompoundItemDescription&>(uapItem);
    const ItemDescriptionVector& items = compoundItem.getItemsVector();
    int allByteCount = 0;
    auto itemCount = items.size();
    ItemDescriptionVector usedItems;
    size_t itemIndex = 1; // zero index is for Variable item itself

    poco_assert(itemCount);
    poco_assert(items[0]->getType() == ItemFormat::Variable);

    for(;;)
    {
        Byte fspec = data[0];
        int mask = 0x80;
        for(int j = 0; j < 7; j++)
        {
            if (fspec & mask)
            {
                poco_assert(itemIndex < items.size());
                poco_assert(items[itemIndex]);
                usedItems.push_back(items[itemIndex]);
            }
            mask >>= 1;
            itemIndex++;
        }

        data++;
        allByteCount++;

        if ((fspec & FX_BIT) == 0)
            break;
    }

    auto usedItemsCount = usedItems.size();
    for(size_t i = 0; i < usedItemsCount; i++)
    {
        const ItemDescription& uapItem = *usedItems[i];
        int decodedByteCount = 0;
        //valueDecoder.item(uapItem);

        switch(uapItem.getType().toValue())
        {
            case ItemFormat::Fixed:
                decodedByteCount = decodeFixed(uapItem, valueDecoder, data);
                break;

            case ItemFormat::Variable:
                decodedByteCount = decodeVariable(uapItem, valueDecoder, data);
                break;

            case ItemFormat::Repetitive:
                decodedByteCount = decodeRepetitive(uapItem, valueDecoder, data);
                break;

            default:
                throw Exception("Unhandled SubItem type: " + uapItem.getType().toString());
        }
        data += decodedByteCount;
        allByteCount += decodedByteCount;
    }

    return allByteCount;
}

} /* namespace astlib */
