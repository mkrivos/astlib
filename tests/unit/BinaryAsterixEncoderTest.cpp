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
        policy(CodecPolicy::Error, true),
        encoder(policy),
        decoder(policy)
    {
        CodecDeclarationLoader loader;
        codecSpecification48 = loader.load("specs/asterix_cat048_1_21.xml");
        codecSpecification62 = loader.load("specs/asterix_cat062_1_16.xml");
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

TEST_F( BinaryDataEncoderTest, mbDataEncode)
{
    std::vector<Byte> buffer;

    auto record = std::make_shared<astlib::SimpleAsterixRecord>();
    record->setItem(astlib::DSI_SAC_CODE, 44);
    record->setItem(DSI_SIC_CODE, 144);
    record->setItem(TIMEOFDAY_CODE, 3600);
    record->setItem(TRACK_DETECTION_CODE, 3);
    record->setItem(TRACK_TEST_CODE, true);
    record->setItem(TRACK_SIMULATED_CODE, true);

    record->setItem(TRACK_POSITION_RANGE_CODE, 10000.0);
    record->setItem(TRACK_POSITION_AZIMUTH_CODE, 45.0);

    record->setItem(MODE3A_V_CODE, true);
    record->setItem(MODE3A_G_CODE, true);
    record->setItem(MODE3A_L_CODE, true);
    record->setItem(MODE3A_VALUE_CODE, 7777);

    record->setItem(AIRCRAFT_IDENTIFICATION_CODE, "PAKON321");
    record->initializeArray(MODES_MBDATA_CODE, 2);
    record->setItem(MODES_MBDATA_CODE, "0123456AB12345", 0);
    record->setItem(MODES_MBDATA_CODE, "01010101ABABAB", 1);

    astlib::SimpleValueEncoder valueEncoder(record);
    encoder.encode(*codecSpecification48, valueEncoder, buffer);

    decoder.decode(*codecSpecification48, valueDecoder, buffer.data(), buffer.size());
    auto record2 = valueDecoder.msg;

    Poco::UInt64 mode3aValue;
    EXPECT_TRUE(record2->getUnsigned(MODE3A_VALUE_CODE, mode3aValue));
    EXPECT_EQ(7777, mode3aValue);

    std::string ident;
    EXPECT_TRUE(record2->getString(AIRCRAFT_IDENTIFICATION_CODE, ident));
    EXPECT_EQ("PAKON321", ident);

    std::string mbdata;
    EXPECT_TRUE(record2->getString(MODES_MBDATA_CODE, mbdata, 0));
    EXPECT_EQ("0123456AB12345", mbdata);

    EXPECT_TRUE(record2->getString(MODES_MBDATA_CODE, mbdata, 1));
    EXPECT_EQ("01010101ABABAB", mbdata);

    EXPECT_THROW(record2->getString(MODES_MBDATA_CODE, mbdata, 2), Poco::Exception);
}

