///
/// \package astlib
/// \file BinaryAsterixEncoder.h
///
/// \author Marian Krivos <nezmar@tutok.sk>
/// \date 20Feb.,2017 
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#pragma once

#include "astlib/CodecPolicy.h"
#include "astlib/model/CodecDescription.h"
#include "ValueEncoder.h"
#include "astlib/ByteUtils.h"

namespace astlib
{

class FspecGenerator;
struct Fixed;

class BinaryAsterixEncoder
{
public:
    static constexpr int MAX_PACKET_SIZE = 8192;

    BinaryAsterixEncoder(CodecPolicy policy = CodecPolicy());
    ~BinaryAsterixEncoder();

    size_t encode(const CodecDescription& codec, ValueEncoder& valueEncoder, std::vector<Byte>& buffer, const std::string& uap = std::string());

private:
    size_t encodePayload(const CodecDescription& codec, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[]);
    size_t encodeFixed(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[]);
    size_t encodeVariable(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[]);
    size_t encodeRepetitive(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[]);
    size_t encodeCompound(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[]);
    size_t encodeExplicit(const ItemDescription& item, ValueEncoder& valueEncoder, const CodecDescription::UapItems& uapItems, FspecGenerator& fspec, Byte buffer[]);
    size_t encodeBitset(const ItemDescription& item, const Fixed& fixed, ValueEncoder& valueEncoder, Byte buffer[], int index);

    CodecPolicy _policy;
};

} /* namespace astlib */

