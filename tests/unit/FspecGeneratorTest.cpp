///
/// \package astlib
/// \file FspecGeneratorTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/encoder/FspecGenerator.h"
#include "gtest/gtest.h"

using namespace astlib;

class FspecGeneratorTest:
    public testing::Test
{
public:
    FspecGeneratorTest()
    {
    }
};

using namespace astlib;

TEST_F(FspecGeneratorTest, basic)
{
    FspecGenerator fspec;
    EXPECT_EQ(1, fspec.size());
    EXPECT_EQ(0x00, fspec.data()[0]);

    fspec.addItem();
    EXPECT_EQ(0x80, fspec.data()[0]);
    EXPECT_EQ(1, fspec.size());

    fspec.addItem();
    EXPECT_EQ(0xC0, fspec.data()[0]);

    fspec.addItem();
    fspec.addItem();
    fspec.addItem();
    fspec.addItem();
    fspec.addItem();
    EXPECT_EQ(0xFE, fspec.data()[0]);
    EXPECT_EQ(1, fspec.size());

    fspec.addItem();
    EXPECT_EQ(0xFF, fspec.data()[0]);
    EXPECT_EQ(0x80, fspec.data()[1]);
    EXPECT_EQ(2, fspec.size());

    fspec.skipItems(6);
    fspec.addItem();
    EXPECT_EQ(0x81, fspec.data()[1]);
    EXPECT_EQ(0x80, fspec.data()[2]);
    EXPECT_EQ(3, fspec.size());
}
