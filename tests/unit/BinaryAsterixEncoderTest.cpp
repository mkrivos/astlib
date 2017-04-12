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
#include "astlib/encoder/SimpleValueEncoder.h"
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
    BinaryDataEncoderTest() :
        encoder(CodecPolicy(CodecPolicy::Error, true)),
        decoder(CodecPolicy(CodecPolicy::Error, true))
    {
        CodecDeclarationLoader loader;
        codecSpecification = loader.load("specs/asterix_cat048_1_21.xml");
        codecSpecification04 = loader.load("specs/asterix_cat004_1_8.xml");
    }
    ~BinaryDataEncoderTest()
    {
    }

    class zeroEncoder :
        public ValueEncoder
    {
        bool encode(const CodecContext& ctx, Poco::UInt64& value, int index)
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
        bool encode(const CodecContext& ctx, Poco::UInt64& value, int index)
        {
            value = Poco::UInt64(0x8877665544332211UL);
            return true;
        }
        virtual size_t getArraySize(AsterixItemCode code) const
        {
            return 1;
        }
    } valueEncoder;

    CodecDescriptionPtr codecSpecification;
    CodecDescriptionPtr codecSpecification04;
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

    //for(unsigned char byte: buffer) std::cout << Poco::NumberFormatter::formatHex(byte, 2, false) << " ";
    //std::cout << std::endl;

    class MyDecoder:
        public SimpleValueDecoder
    {
    public:
        virtual void onMessageDecoded(SimpleAsterixRecordPtr ptr)
        {
            msg = ptr;
        }

        SimpleAsterixRecordPtr msg;
    } valueDecoder;
    decoder.decode(*codecSpecification, valueDecoder, buffer.data(), buffer.size());

    //std::cout << valueDecoder.msg->toString() << std::endl;
}

TEST_F( BinaryDataEncoderTest, simpleEncode)
{
    std::vector<Byte> buffer;
    astlib::CodecPolicy policy;
    policy.verbose = true;
    astlib::BinaryAsterixEncoder encoder(policy);
    astlib::SimpleValueEncoder valueEncoder(std::make_shared<astlib::SimpleAsterixRecord>());
    encoder.encode(*codecSpecification04, valueEncoder, buffer);
}

