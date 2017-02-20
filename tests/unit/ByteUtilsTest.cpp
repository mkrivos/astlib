///
/// \package astlib
/// \file ByteUtilsTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/ByteUtils.h"
#include "gtest/gtest.h"

using namespace astlib;

TEST(ByteUtilsTest, toSigned)
{
    EXPECT_EQ(-128, ByteUtils::toSigned(128, 8));
    EXPECT_EQ( 127, ByteUtils::toSigned(127, 8));

    EXPECT_EQ(-32768, ByteUtils::toSigned(32768, 16));
    EXPECT_EQ( 32767, ByteUtils::toSigned(32767, 16));
}

TEST(ByteUtilsTest, decToOctal)
{
    unsigned value = 7777;
    EXPECT_EQ(07777, ByteUtils::dec2oct(value));
}

TEST(ByteUtilsTest, octalToDec)
{
    unsigned value = 07777;
    EXPECT_EQ(7777, ByteUtils::oct2dec(value));
}

TEST(ByteUtilsTest, pokeBigEndian)
{
    {
        Byte buffer[8];
        ByteUtils::pokeBigEndian(buffer, Poco::UInt64(0x11FFFFFFFFFFFF22UL), 8);
        EXPECT_EQ(0x11, buffer[0]);
        EXPECT_EQ(0x22, buffer[7]);
    }
    {
        Byte buffer[8];
        memset(buffer, 0x44, 8);
        ByteUtils::pokeBigEndian(buffer, Poco::UInt64(0x1122UL), 2);
        EXPECT_EQ(0x11, buffer[0]);
        EXPECT_EQ(0x22, buffer[1]);
        EXPECT_EQ(0x44, buffer[2]);
        EXPECT_EQ(0x44, buffer[3]);
        EXPECT_EQ(0x44, buffer[4]);
        EXPECT_EQ(0x44, buffer[5]);
        EXPECT_EQ(0x44, buffer[6]);
        EXPECT_EQ(0x44, buffer[7]);
    }
}
