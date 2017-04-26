///
/// \package astlib
/// \file CodecRoundtripTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 24.2.2017
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/encoder/BinaryAsterixEncoder.h"
#include "astlib/encoder/SimpleValueEncoder.h"
#include "astlib/decoder/BinaryAsterixDecoder.h"
#include "astlib/decoder/SimpleValueDecoder.h"
#include "astlib/CodecDeclarationLoader.h"
#include "astlib/AsterixItemDictionary.h"
#include "astlib/Exception.h"

#include <Poco/NumberFormatter.h>
#include "gtest/gtest.h"

using namespace astlib;

TEST(CodecRoundtripTest, cat48)
{
    CodecDeclarationLoader loader;
    auto codecSpecification = loader.load("specs/asterix_cat048_1_21.xml");

    unsigned char bytes[111] = {
        48, // CAT
        0, 111, // size
        0xFF, 0xFF, 0xFF, 0xF8,// FSPEC

        5, 6,  // 10 - sac sic
        0, 0, 200, // 140 - time of day
        0xfe, // 20 - Target Report Descriptor
        0xFF, 0x11,0xFF, 0x22, // 40 - polar coords
        0xFF, 0x33, // 70 - mode 3A
        0xFF, 0x44, // 90 - mode C
        0xFE, 0x88, 0x44,0x88, 0x44, 0x88, 0x44, 0x88, // 130 - plot characteristics

        0xFF, 0xFF, 0xFF, // 220 - aircraft address
        0x42, 0x55, 0x12, 0x45, 0x42, 0x24, // 240 - Aircraft Identification @@
        2, 4,4,4,4,4,4,2,1, 5,5,5,5,5,5,2,1,  // item 250 Mode S Comm B data @@
        1,0, // 161 - track number
        0xFF, 0xFF, 0x00, 0x01, // 42 - cartes coords
        0xFF, 0xFF, 0xFF, 0xFF, // 200
        0xFF, 0xFE, // 170 - track status

        0xEE, 0xFF, 0xFF, 0xFF, // 210 - track quality
        6, // 30 - WE Condition @@
        0xFF, 0xFE, // 80 - mode 3a conf
        0xCC, 0xFF, 0xFF, 0xFF, // 100 - mode C conf
        0xDD, 0xFF, // 110 - 3d height
        0xC0, 0xFF,0xFF, 2, 0,1,0,2,0,3, 0,1,0,2,0,3, // 120 - radial dopler speed @@
        0xFF, 0xFF, // 230 - Acas comm

        0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 260 - ACAS resolution
        0xBB, // 55
        0xFF, 0xFF,// 50
        0xFF, // 65
        0xFF, 0xFF,// 60

    };
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

    BinaryAsterixDecoder decoder(CodecPolicy(CodecPolicy::Error, false));
    decoder.decode(*codecSpecification, valueDecoder, bytes, sizeof(bytes));

    EXPECT_EQ(48, valueDecoder.msg->getCategory());

    //std::cout << valueDecoder.msg->toString() << std::endl;

    std::vector<Byte> buffer;
    BinaryAsterixEncoder encoder(CodecPolicy(CodecPolicy::Error, false));
    SimpleValueEncoder valueEncoder(valueDecoder.msg);
    EXPECT_EQ(sizeof(bytes), encoder.encode(*codecSpecification, valueEncoder, buffer));
/*
    for(unsigned char byte: buffer)
        std::cout << Poco::NumberFormatter::formatHex(byte, 2, false) << " ";
    std::cout << valueDecoder.msg->toString() << std::endl;
    std::cout << std::endl;
    */
}
