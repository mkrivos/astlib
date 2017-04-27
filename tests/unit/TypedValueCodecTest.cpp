///
/// \package astlib
/// \file TypedValueCodecTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 24.2.2017
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/model/BitsDescription.h"
#include "astlib/model/FixedItemDescription.h"
#include "astlib/encoder/TypedValueEncoder.h"
#include "astlib/decoder/TypedValueDecoder.h"
#include "astlib/AsterixItemDictionary.h"
#include "astlib/Exception.h"

#include <Poco/NumberFormatter.h>
#include "gtest/gtest.h"

using namespace astlib;

class TypedEncoder :
    public TypedValueEncoder,
    public TypedValueDecoder
{
public:
    virtual void begin(int cat) {}
    virtual void beginItem(const ItemDescription& uapItem) {}
    virtual void beginRepetitive(size_t size) {}
    virtual void end(){}
    virtual void beginArray(AsterixItemCode code, size_t size) {}
    virtual size_t getArraySize(AsterixItemCode code) const { return 0; }

    virtual bool encodeBoolean(const CodecContext& ctx, bool& value, int index)
    {
        return true;
    }

    virtual bool encodeSigned(const CodecContext& ctx, Poco::Int64& value, int index)
    {
        return true;
    }

    virtual bool encodeUnsigned(const CodecContext& ctx, Poco::UInt64& value, int index)
    {
        return true;
    }

    virtual bool encodeReal(const CodecContext& ctx, double& value, int index)
    {
        return true;
    }

    virtual bool encodeString(const CodecContext& ctx, std::string& value, int index)
    {
        value = fromStr;
        return true;
    }


    virtual void decodeBoolean(const CodecContext& ctx, bool value, int index)
    {
    }

    virtual void decodeSigned(const CodecContext& ctx, Poco::Int64 value, int index)
    {
    }

    virtual void decodeUnsigned(const CodecContext& ctx, Poco::UInt64 value, int index)
    {
    }

    virtual void decodeReal(const CodecContext& ctx, double value, int index)
    {
    }

    virtual void decodeString(const CodecContext& ctx, const std::string& value, int index)
    {
        strResult = value;
    }

    std::string fromStr;
    std::string strResult;
};

class TypedValueCodecTest:
    public testing::Test
{
public:
};

TEST_F(TypedValueCodecTest, asciiEncoding)
{
    AsterixItemCode code(1, PrimitiveType::String, false);
    BitsDescription bits(code);
    bits.from = 64;
    bits.to = 1;
    bits.encoding = Encoding::Ascii;
    bits.name = "foo";
    BitsDescriptionArray array { bits };
    Fixed fixed(array, 6);
    FixedItemDescription uapItem(0, "Test", fixed);
    CodecPolicy policy;
    int depth = 1;
    CodecContext ctx(uapItem, policy, bits, depth);
    TypedEncoder encoder;

    encoder.fromStr = "ABCDEFGH";
    Poco::UInt64 value = 0;
    EXPECT_TRUE(encoder.encode(ctx, value, -1));
    EXPECT_EQ(0x4142434445464748ULL, value);

    encoder.decode(ctx, value, -1);
    EXPECT_EQ("ABCDEFGH", encoder.strResult);
}

TEST_F(TypedValueCodecTest, asciiSixbitEncoding)
{
    AsterixItemCode code(1, PrimitiveType::String, false);
    BitsDescription bits(code);
    bits.from = 48;
    bits.to = 1;
    bits.encoding = Encoding::SixBitsChar;
    bits.name = "foo";
    BitsDescriptionArray array { bits };
    Fixed fixed(array, 6);
    FixedItemDescription uapItem(0, "Test", fixed);
    CodecPolicy policy;
    int depth = 1;
    CodecContext ctx(uapItem, policy, bits, depth);
    TypedEncoder encoder;

    Poco::UInt64 value = 0x5054d4c31820ULL;
    encoder.decode(ctx, value, -1);
    EXPECT_EQ("TEST01", encoder.strResult);

    value = 0;
    encoder.fromStr = encoder.strResult;
    EXPECT_TRUE(encoder.encode(ctx, value, -1));
    EXPECT_EQ(0x5054d4c31820ULL, value);

    value = 0x092071c31820ULL;
    encoder.decode(ctx, value, -1);
    EXPECT_EQ("BRA101", encoder.strResult);

    value = 0;
    encoder.fromStr = encoder.strResult;
    EXPECT_TRUE(encoder.encode(ctx, value, -1));
    EXPECT_EQ(0x092071c31820ULL, value);
}
