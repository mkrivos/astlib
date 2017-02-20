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
#include "astlib/decoder/SimpleValueDecoder.h"
#include "astlib/CodecDeclarationLoader.h"
#include "astlib/Exception.h"

#include <Poco/NumberFormatter.h>
#include "gtest/gtest.h"

#include "obj/astlib/AsterixItemDictionary.h"

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
    } zeroEncoder;

    class MyValueEncoder :
        public ValueEncoder
    {
        bool encode(const CodecContext& ctx, Poco::UInt64& value)
        {
            value = Poco::UInt64(0x1122334455667788UL);
            return true;
        }
    } valueEncoder;

    CodecDescriptionPtr codecSpecification;
    BinaryAsterixEncoder encoder;
};

TEST_F( BinaryDataEncoderTest, zeroDecode)
{
    std::vector<Byte> buffer;
    EXPECT_EQ(7, encoder.encode(*codecSpecification, zeroEncoder, buffer, ""));
}

TEST_F( BinaryDataEncoderTest, fullDecode)
{
    std::vector<Byte> buffer;
    EXPECT_EQ(66, encoder.encode(*codecSpecification, valueEncoder, buffer, ""));
}
