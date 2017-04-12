///
/// \package astlib
/// \file BinaryAsterixEncoder.cpp
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 20Feb.,2017 
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
#include <set>


namespace astlib
{

BinaryAsterixEncoder::BinaryAsterixEncoder(CodecPolicy policy) :
    _policy(policy)
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

    auto reducedFspec = fspec.getArray();
    size_t len = 1 + 2 + reducedFspec.size() + encodedSize;
    buffer.resize(len);
    buffer[0] = codec.getCategoryDescription().getCategory();
    // TODO: pre littleendian treba zvlast vetvu
    buffer[1] = (len >> 8) & 0xFF;
    buffer[2] = len & 0xFF;
    if (reducedFspec.size())
    {
        memcpy(&buffer[3], reducedFspec.data(), reducedFspec.size());
        memcpy(&buffer[3 + reducedFspec.size()], aux, encodedSize);
    }
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

        if (_policy.verbose)
            std::cout << "Encoding item " << codec.getCategoryDescription().getCategory() << "/" << item.getId() << ": " << item.getDescription() << std::endl;

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
                len = encodeExplicit(item, valueEncoder, uapItems, fspec, buffer + bufferPosition);
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
    return encodeBitset(item, fixed, valueEncoder, buffer, -1);
}

size_t BinaryAsterixEncoder::encodeVariable(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    const VariableItemDescription& varItem = static_cast<const VariableItemDescription&>(item);
    const FixedVector& fixedVector = varItem.getFixedVector();
    auto ptr = buffer;
    size_t encodedByteCount = 0;

    for(const Fixed& fixed: fixedVector)
    {
        poco_assert(fixed.length == 1);
        auto len = encodeBitset(item, fixed, valueEncoder, ptr, -1);
        encodedByteCount += len;
        ptr += len;
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
        for(size_t i = 0; i < encodedByteCount-1; i++)
        {
            ptr[i-encodedByteCount] |= FX_BIT;
        }
    }

    return encodedByteCount;
}

size_t BinaryAsterixEncoder::encodeRepetitive(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    const RepetitiveItemDescription& varItem = static_cast<const RepetitiveItemDescription&>(item);
    const FixedVector& fixedVector = varItem.getFixedVector();

    poco_assert(fixedVector.size());
    auto& bits = fixedVector.front().bitsDescriptions.front();
    AsterixItemCode firstItemCode = bits.code;
    poco_assert_msg(firstItemCode.isArray(), bits.toString().c_str());

    //valueEncoder.
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
            allByteCount += encodeBitset(item, fixed, valueEncoder, buffer + allByteCount, i);
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
    std::set<int> encodedIds;
    size_t index = 0;

    for(ItemDescriptionPtr uapItem: items)
    {
        int encodedByteCount = 0;

        if (index == 0)
        {
            ++index;
            continue;
        }

        switch(uapItem->getType().toValue())
        {
            case ItemFormat::Fixed:
                encodedByteCount = encodeFixed(*uapItem, valueEncoder, uapItems, localFspec, local+allByteCount);
                break;

            case ItemFormat::Variable:
                encodedByteCount = encodeVariable(*uapItem, valueEncoder, uapItems, localFspec, local+allByteCount);
                break;

            case ItemFormat::Repetitive:
                encodedByteCount = encodeRepetitive(*uapItem, valueEncoder, uapItems, localFspec, local+allByteCount);
                break;

            default:
                throw Exception("Unhandled SubItem type: " + uapItem->getType().toString());
        }

        if (encodedByteCount)
        {
            encodedIds.insert(index);
            allByteCount += encodedByteCount;
        }

        index++;
    }

    if (allByteCount == 0)
    {
        poco_assert(encodedIds.empty());
        return 0;
    }

    // TODO: zobrat redukovany fspec, pridat local buffer
    const VariableItemDescription& variableItem = dynamic_cast<const VariableItemDescription&>(*items[0]);
    const FixedVector& fixedVector = variableItem.getFixedVector();
    std::vector<Byte> variableFspec;

    for(const Fixed& fixed: fixedVector)
    {
        poco_assert(fixed.length == 1);
        const BitsDescriptionArray& bitsArray = fixed.bitsDescriptions;
        Byte presenceByte = 0;

        for(const BitsDescription& bits: bitsArray)
        {
            if (bits.presence != 0)
            {
                if (encodedIds.find(bits.presence) != encodedIds.end())
                {
                    presenceByte |= (1 << (bits.bit-1));
                }
            }
        }
        variableFspec.push_back(presenceByte);
    }

    auto finalFspec = FspecGenerator::reduce(variableFspec);
    memcpy(buffer, finalFspec.data(), finalFspec.size());
    memcpy(buffer+finalFspec.size(), local, allByteCount);

    return finalFspec.size() + allByteCount;
}

size_t BinaryAsterixEncoder::encodeExplicit(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[])
{
    return 0;
}

size_t BinaryAsterixEncoder::encodeBitset(const ItemDescription& item, const Fixed& fixed, ValueEncoder& valueEncoder, Byte buffer[], int index)
{
    const BitsDescriptionArray& bitsDescriptions = fixed.bitsDescriptions;
    Poco::UInt64 data = 0;
    bool encoded = false;

    for (const BitsDescription& bits : bitsDescriptions)
    {
        CodecContext context(item, _policy, bits, 0);
        Poco::UInt64 value = 0;

        if (valueEncoder.encode(context, value, index))
        {
            // TODO: obsluha rozsahu - treba detekovat pretecenie a nasledne bud hodit chybu alebo zalimitovat
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

            if (_policy.verbose)
            {
                if (index == -1)
                    std::cout << " " << bits.name << " = " << (value&mask) << " size = " << context.width/8 << std::endl;
                else
                    std::cout << " " << bits.name << "[" << index << "] = " << (value&mask) << " size = " << context.width/8 << std::endl;
            }

            data |= ((value & mask) << leftShift);
        }
    }

    if (encoded)
    {
        int len = fixed.length;
        ByteUtils::pokeBigEndian(buffer, data, len);
        if (_policy.verbose)
        {
            std::cout << "  " << Poco::NumberFormatter::formatHex(data, len*2) << std::endl;
        }
        return len;
    }

    return 0;
}

} /* namespace astlib */
