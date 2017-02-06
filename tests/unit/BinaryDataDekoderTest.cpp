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

#include "astlib/CodecDeclarationLoader.h"
#include "astlib/BinaryDataDekoder.h"
#include "astlib/Exception.h"
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


public:
    void SetUp()
    {
    }

    CodecDescriptionPtr codecSpecification;
};

TEST_F( BinaryDataDekoderTest, decodeCat48)
{
    BinaryDataDekoder dekoder;
    unsigned char bytes0[3] = { 48, 0, 0};
    EXPECT_THROW(dekoder.decode(*codecSpecification, bytes0, sizeof(bytes0)), Exception);
}
