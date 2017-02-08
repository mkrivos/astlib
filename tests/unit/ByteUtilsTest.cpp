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
