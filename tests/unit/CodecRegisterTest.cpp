///
/// \package astlib
/// \file CodecRegisterTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/CodecRegister.h"
#include "gtest/gtest.h"

using namespace astlib;

TEST(CodecRegisterTest, populateCodecsFromDirectory)
{
    CodecRegister codecRegister;

    codecRegister.populateCodecsFromDirectory("specs");
    EXPECT_EQ(21, codecRegister.enumerateAllCodecs().size());
    EXPECT_EQ(19, codecRegister.enumerateCodecsByCategory().size());
}
