///
/// \package astlib
/// \file BinaryAsterixEncoder.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 20Feb.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "BinaryAsterixEncoder.h"
#include "ValueEncoder.h"
#include "FspecGenerator.h"
#include "astlib/model/FixedItemDescription.h"
#include "astlib/model/VariableItemDescription.h"
#include "astlib/model/CompoundItemDescription.h"
#include "astlib/model/RepetitiveItemDescription.h"
#include "astlib/Exception.h"

#include <iostream>


namespace astlib
{

BinaryAsterixEncoder::BinaryAsterixEncoder()
{
}

BinaryAsterixEncoder::~BinaryAsterixEncoder()
{
}

size_t BinaryAsterixEncoder::encode(const CodecDescription& codec, ValueEncoder& valueEncoder, std::vector<Byte>& buffer, const std::string& uap)
{
    FspecGenerator fspec;
    Byte aux[MAX_PACKET_SIZE];

    const CodecDescription::UapItems& uapItems = codec.enumerateUapItems();
    size_t encodedSize = encodePayload(codec, valueEncoder, uapItems, fspec, aux);

    size_t len = 1 + 2 + fspec.size() + encodedSize;
    buffer.resize(len);
    buffer[0] = codec.getCategoryDescription().getCategory();
    // TODO: pre littleendian treba zvlast vetvu
    buffer[1] = (len >> 8) & 0xFF;
    buffer[2] = len & 0xFF;
    memcpy(&buffer[3], fspec.data(), fspec.size());
    memcpy(&buffer[3+fspec.size()], aux, encodedSize);

    return len;
}

size_t BinaryAsterixEncoder::encodePayload(const CodecDescription& codec, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    size_t bufferPosition = 0;

    for(const auto& entry: uapItems)
    {
        if (!entry.second.item)
        {
            fspec.skipItem();
            continue;
        }

        const ItemDescription& item = *entry.second.item;
        size_t len = 0;

        switch(item.getType().toValue())
        {
            case ItemFormat::Fixed:
                len = encodeFixed(item, valueEncoder, uapItems, fspec, buffer + bufferPosition);
                break;
            case ItemFormat::Variable:
                len = encodeVariable(item, valueEncoder, uapItems, fspec, buffer + bufferPosition);
                break;
            case ItemFormat::Repetitive:
                len = encodeRepetitive(item, valueEncoder, uapItems, fspec, buffer + bufferPosition);
                break;
            case ItemFormat::Compound:
                len = encodeCompound(item, valueEncoder, uapItems, fspec, buffer + bufferPosition);
                break;
            case ItemFormat::Explicit:
             //   len = encodeExplicit(item, valueEncoder, uapItems, fspec, buffer + bufferPosition);
                break;
        }

        if (len > 0)
        {
            bufferPosition += len;
            fspec.addItem();
        }
        else
        {
            fspec.skipItem();
        }
    }

    return bufferPosition;
}

size_t BinaryAsterixEncoder::encodeFixed(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    const FixedItemDescription& fixedItem = static_cast<const FixedItemDescription&>(item);
    const Fixed& fixed = fixedItem.getFixed();
    return encodeBitset(item, fixed, valueEncoder, buffer);
}

size_t BinaryAsterixEncoder::encodeVariable(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    const VariableItemDescription& varItem = static_cast<const VariableItemDescription&>(item);
    const FixedVector& fixedVector = varItem.getFixedVector();
    auto ptr = buffer;
    int encodedByteCount = 0;

    for(const Fixed& fixed: fixedVector)
    {
        auto len = fixed.length;
        poco_assert(len == 1);
        encodeBitset(item, fixed, valueEncoder, ptr);
        encodedByteCount++;
        ptr++;
    }

    if (encodedByteCount > 1)
    {
        auto aux = ptr-1;
        for(int i = encodedByteCount-1; i > 0; i--)
        {
            if (*aux == 0)
            {
                encodedByteCount--;
            }
            else
            {
                break;
            }
        }
    }

    if (encodedByteCount > 1)
    {
        for(int i = 0; i < encodedByteCount-1; i++)
        {
            ptr[i] |= FX_BIT;
        }
    }

    return encodedByteCount;
}

size_t BinaryAsterixEncoder::encodeRepetitive(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    const RepetitiveItemDescription& varItem = static_cast<const RepetitiveItemDescription&>(item);
    const FixedVector& fixedVector = varItem.getFixedVector();

    poco_assert(fixedVector.size());
    AsterixItemCode firstItemCode = fixedVector.front().bitsDescriptions.front().code;
    poco_assert(firstItemCode.isArray());

    auto count = valueEncoder.getArraySize(firstItemCode);
    // Empty array - no encoding
    if (count == 0)
        return 0;

    auto bufferStart = buffer++;
    size_t allByteCount = 0;

    for(size_t i = 0; i < count; i++)
    {
        for(const Fixed& fixed: fixedVector)
        {
            allByteCount = encodeBitset(item, fixed, valueEncoder, buffer);
            buffer += allByteCount;
        }
    }

    // save repetition count
    *bufferStart = Byte(count);

    return 1+allByteCount;
}

size_t BinaryAsterixEncoder::encodeCompound(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    const CompoundItemDescription& compoundItem = static_cast<const CompoundItemDescription&>(item);
    const ItemDescriptionVector& items = compoundItem.getItemsVector();
    Byte local[MAX_PACKET_SIZE/2];
    FspecGenerator localFspec;
    size_t allByteCount = 0;

    // One variable + one more minimally
    poco_assert(items.size() > 1);
    std::vector<int> encodedIds;
    int index = 0;

    for(ItemDescriptionPtr uapItem: items)
    {
        int decodedByteCount = 0;

        if (index == 0)
        {
            ++index;
            continue;
        }

        switch(uapItem->getType().toValue())
        {
            case ItemFormat::Fixed:
                decodedByteCount = encodeFixed(*uapItem, valueEncoder, uapItems, localFspec, local+allByteCount);
                break;

            case ItemFormat::Variable:
                decodedByteCount = encodeVariable(*uapItem, valueEncoder, uapItems, localFspec, local+allByteCount);
                break;

            case ItemFormat::Repetitive:
                decodedByteCount = encodeRepetitive(*uapItem, valueEncoder, uapItems, localFspec, local+allByteCount);
                break;

            default:
                throw Exception("Unhandled SubItem type: " + uapItem->getType().toString());
        }

        if (decodedByteCount)
        {
            encodedIds.push_back(index);
            allByteCount += decodedByteCount;
        }

        index++;
    }

    // TODO: zobrat redukovany fspec, pridat local buffer
    const VariableItemDescription& variableItem = dynamic_cast<const VariableItemDescription&>(*items[0]);

    return allByteCount;
}

size_t BinaryAsterixEncoder::encodeExplicit(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    return 0;
}

size_t BinaryAsterixEncoder::encodeBitset(const ItemDescription& item, const Fixed& fixed, ValueEncoder& valueEncoder, Byte buffer[])
{
    const BitsDescriptionArray& bitsDescriptions = fixed.bitsDescriptions;
    Poco::UInt64 data = 0;
    bool encoded = false;

    for (const BitsDescription& bits : bitsDescriptions)
    {
        CodecContext context(item, bits, 0);
        Poco::UInt64 value = 0;

        if (valueEncoder.encode(context, value))
        {
            encoded = true;
            Poco::UInt64 mask = 0;
            int leftShift = 0;

            if (context.width == 1)
            {
                // Send non FX bits only
                if (!bits.fx)
                {
                    mask = 1;
                    leftShift = bits.bit-1;
                }
            }
            else
            {
                mask = bits.bitMask();
                leftShift = bits.to-1;
            }
std::cout << bits.name << " = " << (value&mask) << " size = " << context.width << std::endl;
            data |= ((value & mask) << leftShift);
        }
    }

    if (encoded)
    {
        int len = fixed.length;
        ByteUtils::pokeBigEndian(buffer, data, len);
std::cout << "  " << Poco::NumberFormatter::formatHex(data) << std::endl;
        return len;
    }

    return 0;
}

} /* namespace astlib */
