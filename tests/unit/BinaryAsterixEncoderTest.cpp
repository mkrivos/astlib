///
/// \package astlib
/// \file BinaryDataEncoderTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/encoder/BinaryAsterixEncoder.h"
#include "astlib/decoder/BinaryAsterixDecoder.h"
#include "astlib/decoder/SimpleValueDecoder.h"
#include "astlib/decoder/JsonValueDecoder.h"
#include "astlib/CodecDeclarationLoader.h"
#include "astlib/AsterixItemDictionary.h"
#include "astlib/Exception.h"

#include <Poco/NumberFormatter.h>
#include "gtest/gtest.h"


using namespace astlib;

class BinaryDataEncoderTest:
    public testing::Test
{
public:
    BinaryDataEncoderTest()
    {
        CodecDeclarationLoader loader;
        codecSpecification = loader.load("specs/asterix_cat048_1_21.xml");
    }
    ~BinaryDataEncoderTest()
    {
    }

    class zeroEncoder :
        public ValueEncoder
    {
        bool encode(const CodecContext& ctx, Poco::UInt64& value)
        {
            return false;
        }
        virtual size_t getArraySize(AsterixItemCode code) const
        {
            return 0;
        }
    } zeroEncoder;

    class MyValueEncoder :
        public ValueEncoder
    {
        bool encode(const CodecContext& ctx, Poco::UInt64& value)
        {
            value = Poco::UInt64(0x8877665544332211UL);
            return true;
        }
        virtual size_t getArraySize(AsterixItemCode code) const
        {
            return 2;
        }
    } valueEncoder;

    CodecDescriptionPtr codecSpecification;
    BinaryAsterixEncoder encoder;
    BinaryAsterixDecoder decoder;
};

TEST_F( BinaryDataEncoderTest, zeroEncode)
{
    std::vector<Byte> buffer;
    EXPECT_EQ(3, encoder.encode(*codecSpecification, zeroEncoder, buffer, ""));
}

TEST_F( BinaryDataEncoderTest, fullEncode)
{
    std::vector<Byte> buffer;
    EXPECT_EQ(98, encoder.encode(*codecSpecification, valueEncoder, buffer, ""));

    JsonValueDecoder valueDecoder;
    decoder.decode(*codecSpecification, valueDecoder, buffer.data(), buffer.size());
}
