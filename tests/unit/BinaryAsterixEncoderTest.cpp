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
#include "astlib/specifications/entries.h"
#include "astlib/CodecDeclarationLoader.h"
#include "astlib/AsterixItemDictionary.h"
#include "astlib/Exception.h"

#include <Poco/NumberFormatter.h>
#include <Poco/Path.h>
#include "gtest/gtest.h"
#include <iostream>


using namespace astlib;

class BinaryDataEncoderTest:
    public testing::Test
{
public:
    BinaryDataEncoderTest() :
        policy(CodecPolicy::Error, true),
        encoder(policy),
        decoder(policy)
    {
		std::cout << Poco::Path::current() << std::endl;

        CodecDeclarationLoader loader;

        std::istringstream stream48(std::string(astlib::cat048_1_21));
        codecSpecification48 = loader.parse(stream48);

        std::istringstream stream62(std::string(astlib::cat062_1_16));
        codecSpecification62 = loader.parse(stream62);

        std::istringstream stream04(std::string(astlib::cat004_1_8));
        codecSpecification04 = loader.parse(stream04);
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

    CodecDescriptionPtr codecSpecification04;
    CodecDescriptionPtr codecSpecification48;
    CodecDescriptionPtr codecSpecification62;
    astlib::CodecPolicy policy;
    BinaryAsterixEncoder encoder;
    BinaryAsterixDecoder decoder;
};

TEST_F( BinaryDataEncoderTest, zeroEncode)
{
    std::vector<Byte> buffer;
    EXPECT_EQ(3, encoder.encode(*codecSpecification48, zeroEncoder, buffer, ""));
}

TEST_F( BinaryDataEncoderTest, fullEncode)
{
    std::vector<Byte> buffer;
    EXPECT_EQ(98, encoder.encode(*codecSpecification48, valueEncoder, buffer, ""));

    //for(unsigned char byte: buffer) std::cout << Poco::NumberFormatter::formatHex(byte, 2, false) << " ";
    //std::cout << std::endl;

    decoder.decode(*codecSpecification48, valueDecoder, buffer.data(), buffer.size());

    //std::cout << valueDecoder.msg->toString() << std::endl;
}

TEST_F( BinaryDataEncoderTest, simpleEncode04)
{
    std::vector<Byte> buffer;
    astlib::SimpleValueEncoder valueEncoder(std::make_shared<astlib::SimpleAsterixRecord>());
    encoder.encode(*codecSpecification04, valueEncoder, buffer);
}

TEST_F( BinaryDataEncoderTest, simpleEncode48)
{
    std::vector<Byte> buffer;
    astlib::SimpleValueEncoder valueEncoder(std::make_shared<astlib::SimpleAsterixRecord>());
    encoder.encode(*codecSpecification48, valueEncoder, buffer);
}

TEST_F( BinaryDataEncoderTest, simpleEncode62)
{
    std::vector<Byte> buffer;
    astlib::SimpleValueEncoder valueEncoder(std::make_shared<astlib::SimpleAsterixRecord>());
    encoder.encode(*codecSpecification62, valueEncoder, buffer);
}

TEST_F( BinaryDataEncoderTest, aircraftDerivedData62)
{
    auto record = std::make_shared<astlib::SimpleAsterixRecord>();

    record->initializeArray(astlib::TRAJECTORY_INTENT_TCP_UNAVAILABLE, 2);
    record->setItem(astlib::TRAJECTORY_INTENT_TCP_UNAVAILABLE, true, 0);
    record->setItem(astlib::TRAJECTORY_INTENT_TCP_UNAVAILABLE, false, 1);

    record->initializeArray(astlib::TRAJECTORY_INTENT_TCP_LATITUDE, 2);
    record->setItem(astlib::TRAJECTORY_INTENT_TCP_LATITUDE, 42.67, 0);
    record->setItem(astlib::TRAJECTORY_INTENT_TCP_LATITUDE, -6.7, 1);

    record->initializeArray(astlib::TRAJECTORY_INTENT_TCP_LONGITUDE, 2);
    record->setItem(astlib::TRAJECTORY_INTENT_TCP_LONGITUDE, 42.67, 0);
    record->setItem(astlib::TRAJECTORY_INTENT_TCP_LONGITUDE, -6.7, 1);

    std::vector<Byte> buffer;
    astlib::SimpleValueEncoder valueEncoder(record);
    encoder.encode(*codecSpecification62, valueEncoder, buffer);

    for(unsigned char byte: buffer)
        std::cout << Poco::NumberFormatter::formatHex(byte, 2, false) << " ";
    std::cout << std::endl;

    decoder.decode(*codecSpecification62, valueDecoder, buffer.data(), buffer.size());
    auto record2 = valueDecoder.msg;
    //std::cout << record2->toString() << std::endl;
    double value;
    EXPECT_TRUE(record2->hasItem(astlib::TRAJECTORY_INTENT_TCP_LATITUDE));
    EXPECT_TRUE(record2->getReal(astlib::TRAJECTORY_INTENT_TCP_LATITUDE, value, 0));
    EXPECT_NEAR(42.67, value, 0.001);
    EXPECT_TRUE(record2->getReal(astlib::TRAJECTORY_INTENT_TCP_LATITUDE, value, 1));
    EXPECT_NEAR(-6.7, value, 0.01);
}

TEST_F( BinaryDataEncoderTest, mbDataEncode)
{
    std::vector<Byte> buffer;

    auto record = std::make_shared<astlib::SimpleAsterixRecord>();
    record->setItem(DSI_SAC, 44);
    record->setItem(DSI_SIC, 144);
    record->setItem(TIMEOFDAY, 3600);
    record->setItem(TRACK_DETECTION, 3);
    record->setItem(TRACK_TEST, true);
    record->setItem(TRACK_SIMULATED, true);

    record->setItem(TRACK_POSITION_RANGE, 10000.0);
    record->setItem(TRACK_POSITION_AZIMUTH, 45.0);

    record->setItem(MODE3A_V, true);
    record->setItem(MODE3A_G, true);
    record->setItem(MODE3A_L, true);
    record->setItem(MODE3A_VALUE, 7777);

    record->setItem(TARGET_IDENTIFICATION, "PAKON321");
    record->initializeArray(MODES_MBDATA, 2);
    record->setItem(MODES_MBDATA, "0123456AB12345", 0);
    record->setItem(MODES_MBDATA, "01010101ABABAB", 1);

    astlib::SimpleValueEncoder valueEncoder(record);
    encoder.encode(*codecSpecification48, valueEncoder, buffer);

    decoder.decode(*codecSpecification48, valueDecoder, buffer.data(), buffer.size());
    auto record2 = valueDecoder.msg;

    Poco::UInt64 mode3aValue;
    EXPECT_TRUE(record2->getUnsigned(MODE3A_VALUE, mode3aValue));
    EXPECT_EQ(7777, mode3aValue);

    std::string ident;
    EXPECT_TRUE(record2->getString(TARGET_IDENTIFICATION, ident));
    EXPECT_EQ("PAKON321", ident);

    std::string mbdata;
    EXPECT_TRUE(record2->getString(MODES_MBDATA, mbdata, 0));
    EXPECT_EQ("0123456AB12345", mbdata);

    EXPECT_TRUE(record2->getString(MODES_MBDATA, mbdata, 1));
    EXPECT_EQ("01010101ABABAB", mbdata);

    EXPECT_THROW(record2->getString(MODES_MBDATA, mbdata, 2), Poco::Exception);
}

