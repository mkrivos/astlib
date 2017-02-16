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

#include "astlib/BinaryAsterixDekoder.h"
#include "astlib/decoder/EmptyValueDecoder.h"
#include "astlib/decoder/SimpleValueDecoder.h"
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
        codecSpecification1 = BinaryAsterixDekoder(loader.load("specs/asterix_cat048_1_14.xml"));
        codecSpecification2 = BinaryAsterixDekoder(loader.load("specs/asterix_cat048_1_21.xml"));
    }
    ~BinaryDataDekoderTest()
    {
    }


    class MyValueDecoder :
        public TypedValueDecoder
    {
        virtual void begin()
        {
            std::cout << "Start -------------------------\n";
        }
        virtual void dataItem(const ItemDescription& uapItem)
        {
            std::cout << uapItem.getId() << " - " << uapItem.getDescription() << std::endl;
        }
        virtual void beginRepetitive(int)
        {
        }
        virtual void repetitiveItem(int index)
        {
            std::cout << " [" << index << "]" << std::endl;
        }
        virtual void endRepetitive()
        {
        }
#if 0
        virtual void decode(Poco::UInt64 value, const Context& ctx)
        {
            std::cout << "  " << ctx.bits.name << " = " << Poco::NumberFormatter::formatHex(value, "0") << std::endl;
            if (ctx.bits.name == "FX")
            {
                std::cout << std::endl;
            }
        }
#else
        virtual void decodeBoolean(const std::string& identification, bool value)
        {
            std::cout << "  Boolean " << identification << " = " << Poco::NumberFormatter::format(value) << std::endl;
        }
        virtual void decodeSigned(const std::string& identification, Poco::Int64 value)
        {
            std::cout << "  Integer " << identification << " = " << Poco::NumberFormatter::format(value) << std::endl;
        }
        virtual void decodeUnsigned(const std::string& identification, Poco::UInt64 value)
        {
            std::cout << "  Unsigned " << identification << " = " << Poco::NumberFormatter::format(value) << std::endl;
        }
        virtual void decodeReal(const std::string& identification, double value)
        {
            std::cout << "  Real " << identification << " = " << Poco::NumberFormatter::format(value) << std::endl;
        }
        virtual void decodeString(const std::string& identification, const std::string& value)
        {
            std::cout << "  Real " << identification << " = '" << value << "'" << std::endl;
        }
#endif
        virtual void end()
        {
            std::cout << "End\n";
        }
    } valueDecoder;

    class MySimpleValueDecoder :
        public SimpleValueDecoder
    {
        virtual void onMessageDecoded(SimpleAsterixMessagePtr ptr)
        {
        }
    } defaultDecoder;

    EmptyValueDecoder emptyDecoder;
    BinaryAsterixDekoder codecSpecification1;
    BinaryAsterixDekoder codecSpecification2;
    BinaryAsterixDekoder dekoder;

    static constexpr int SIZE = 1+2+3+2+3+2+4+2+2+8+3+6+2+4+2+2;
    unsigned char standardMessage[SIZE] = {
        48, // CAT
        0, SIZE,
        0xFF, 0xDB, 0x08,// FSPEC

        5, 6,  // 10 - sac sic
        0, 0, 200, // 140 - time of day
        0xFF, 0xFE, // 20 - Target Report Descriptor
        0xFF, 0xFF,0xFF, 0xFF, // 40 - polar coords
        0xFF, 0xFF, // 70 - mode 3A
        0xFF, 0xFF, // 90 - mode C
        0xFE, 0x88, 0x44,0x88, 0x44, 0x88, 0x44, 0x88, // 130 - plot characteristics

        0xFF, 0xFF, 0xFF, // 220 - aircraft address
        0x42, 0x55, 0x12, 0x45, 0x42, 0x24, // 240 - Aircraft Identification
        1,0, // 161 - track number
        0xFF, 0xFF, 0x00, 0x01, // 42 - cartes coords
        0xFF, 0xFE, // 170 - track status

        0xFF, 0xFF, // 110 - 3d height
    };
};

TEST_F( BinaryDataDekoderTest, badDecode)
{
    // too small packet
    {
        unsigned char bytes[3] = { 48, 0, 0};
        EXPECT_THROW(codecSpecification2.decode(valueDecoder, bytes, sizeof(bytes)), Exception);
    }
    // bad lenght
    {
        unsigned char bytes[6] = { 48, 0, 0, 0, 0, 0};
        EXPECT_THROW(codecSpecification2.decode(valueDecoder, bytes, sizeof(bytes)), Exception);
    }
    // no fspec data
    {
        unsigned char bytes[6] = { 48, 0, 6, 0, 0, 0};
        EXPECT_THROW(codecSpecification2.decode(valueDecoder, bytes, sizeof(bytes)), Exception);
    }
}

TEST_F( BinaryDataDekoderTest, decodeCat48MultiRecord)
{
    unsigned char bytes[9] = { 48, 0, 9, 0x80, 1, 2,   0x80, 3, 4 };
    codecSpecification1.decode(valueDecoder, bytes, sizeof(bytes));
}

TEST_F( BinaryDataDekoderTest, completeProfileDecodeCat48)
{
    unsigned char bytes[113] = {
        48, // CAT
        0, 113, // size
        0xFF, 0xFF, 0xFF, 0xF8,// FSPEC

        5, 6,  // 10 - sac sic
        0, 0, 200, // 140 - time of day
        0xfe, // 20 - Target Report Descriptor
        0xFF, 0xFF,0xFF, 0xFF, // 40 - polar coords
        0xFF, 0xFF, // 70 - mode 3A
        0xFF, 0xFF, // 90 - mode C
        0xFE, 0x88, 0x44,0x88, 0x44, 0x88, 0x44, 0x88, // 130 - plot characteristics

        0xFF, 0xFF, 0xFF, // 220 - aircraft address
        0x42, 0x55, 0x12, 0x45, 0x42, 0x24, // 240 - Aircraft Identification
        2, 4,4,4,4,4,4,2,1,  5,5,5,5,5,5,2,1,  // item 250 Mode S Comm B data
        1,0, // 161 - track number
        0xFF, 0xFF, 0x00, 0x01, // 42 - cartes coords
        0xFF, 0xFF, 0xFF, 0xFF, // 200
        0xFF, 0xFE, // 170 - track status

        0xFF, 0xFF, 0xFF, 0xFF, // 210 - track quality
        3,5,6, // 30 - WE Condition
        0xFF, 0xFE, // 80 - mode 3a conf
        0xFF, 0xFF, 0xFF, 0xFF, // 100 - mode C conf
        0xFF, 0xFF, // 110 - 3d height
        0xC0, 0xFF,0xFF, 2, 0,1,0,2,0,3, 0,1,0,2,0,3, // 120 - radial dopler speed
        0xFF, 0xFF, // 230 - Acas comm

        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 260 - ACAS resolution
        0xFF, // 55
        0xFF, 0xFF,// 50
        0xFF, // 65
        0xFF, 0xFF,// 60

    };
    codecSpecification1.decode(valueDecoder, bytes, sizeof(bytes));
    codecSpecification2.decode(valueDecoder, bytes, sizeof(bytes));
}

TEST_F(BinaryDataDekoderTest, cpuBoundDecodeCat48Empty)
{
    for(int i = 0; i < 500000; i++)
    {
        codecSpecification2.decode(emptyDecoder, standardMessage, sizeof(standardMessage));
    }
}

TEST_F(BinaryDataDekoderTest, cpuBoundDecodeCat48Simple)
{
    for(int i = 0; i < 10000; i++)
    {
        codecSpecification2.decode(defaultDecoder, standardMessage, sizeof(standardMessage));
    }
}
