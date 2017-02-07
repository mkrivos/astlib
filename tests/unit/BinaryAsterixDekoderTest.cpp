///
/// \package astlib
/// \file BinaryDataDekoderTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "../../astlib/BinaryAsterixDekoder.h"

#include "astlib/CodecDeclarationLoader.h"
#include "astlib/Exception.h"

#include <Poco/NumberFormatter.h>
#include "gtest/gtest.h"

using namespace astlib;

class BinaryDataDekoderTest:
    public testing::Test
{
public:
    BinaryDataDekoderTest()
    {
        CodecDeclarationLoader loader;
        codecSpecification = loader.load("specs/asterix_cat048_1_14.xml");
    }
    ~BinaryDataDekoderTest()
    {
    }


    class MyValueDecoder :
        public ValueDecoder
    {
        virtual void begin()
        {
            std::cout << "Start ----------\n";
        }
        virtual void item(const ItemDescription& uapItem)
        {
            std::cout << uapItem.getId() << " - " << uapItem.getDescription() << std::endl;
        }
        virtual void decode(Poco::UInt64 value, const BitsDescription& bits)
        {
            std::cout << "  " << bits.name << " = " << Poco::NumberFormatter::format(value) << std::endl;
        }
        virtual void end()
        {
            std::cout << "End\n";
        }
    } valueDecoder;


    CodecDescriptionPtr codecSpecification;
    BinaryAsterixDekoder dekoder;
};

TEST_F( BinaryDataDekoderTest, badDecode)
{
    // too small packet
    {
        unsigned char bytes[3] = { 48, 0, 0};
        EXPECT_THROW(dekoder.decode(*codecSpecification, valueDecoder, bytes, sizeof(bytes)), Exception);
    }
    // bad lenght
    {
        unsigned char bytes[6] = { 48, 0, 0, 0, 0, 0};
        EXPECT_THROW(dekoder.decode(*codecSpecification, valueDecoder, bytes, sizeof(bytes)), Exception);
    }
    // no fspec data
    {
        unsigned char bytes[6] = { 48, 0, 6, 0, 0, 0};
        EXPECT_THROW(dekoder.decode(*codecSpecification, valueDecoder, bytes, sizeof(bytes)), Exception);
    }
    // onr more byte
    {
        unsigned char bytes[7] = { 48, 0, 6, 0x80, 1, 2, 0};
        //EXPECT_THROW(dekoder.decode(*codecSpecification, valueDecoder, bytes, sizeof(bytes)), Exception);
    }
}

TEST_F( BinaryDataDekoderTest, decodeCat48MultiRecord)
{
    unsigned char bytes[9] = { 48, 0, 9, 0x80, 1, 2,   0x80, 3, 4 };
    dekoder.decode(*codecSpecification, valueDecoder, bytes, sizeof(bytes));
}

TEST_F( BinaryDataDekoderTest, decodeCat48)
{
    unsigned char bytes[33+16+2+2+8+3] = {
        48, // CAT
        0, 1+2+3+2+3+1+4+2+2+3+17+16, // size
        0xFF, 0xA1, 0x04, // FSPEC
        5, 6,  // 10 - sac sic
        0, 0, 200, // 140 - time of day
        0xfe, // 20 - Target Report Descriptor
        0, 10, 0, 20, // 40 - polar coords
        0xff, 0xff, // 70 - mode 3A
        0xff, 0xff, // 90 - mode C
        0xFE, 0x88, 0x44,0x88, 0x44, 0x88, 0x44, 0x88, // 130 - plot characteristics
        0xFF, 0xFF, 0xFF, // 220 - aircraft address
        2, 4,4,4,4,4,4,4,4,  5,5,5,5,5,5,5,5,  // item 250 Mode S Comm B data
        0xC0, 0xff,0xFF, 2, 0,1,0,2,0,3, 0,1,0,2,0,3, // 120 - radial dopler speed
    };
    dekoder.decode(*codecSpecification, valueDecoder, bytes, sizeof(bytes));
}
