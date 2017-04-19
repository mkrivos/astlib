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

class CodecRegisterTest:
    public testing::Test
{
public:
    CodecRegisterTest()
    {
        codecRegister.populateCodecsFromDirectory("specs");
    }
    CodecRegister codecRegister;
};

TEST_F(CodecRegisterTest, populateCodecsFromDirectory)
{
    EXPECT_EQ(5, codecRegister.enumerateAllCodecs().size());
    EXPECT_EQ(5, codecRegister.enumerateAllCodecsByCategory().size());
}

TEST_F(CodecRegisterTest, getLatestCodecForCategory)
{
    auto codec = codecRegister.getLatestCodecForCategory(48);
    ASSERT_TRUE(codec.get());

    const CodecDescription::Dictionary symbols = codec->getDictionary();
    EXPECT_EQ(144, symbols.size());
}

TEST_F(CodecRegisterTest, getCodecForString)
{
    auto codec = codecRegister.getCodecForSignature("Eurocontrol-48:1.21");
    ASSERT_TRUE(codec.get());

    EXPECT_EQ(48, codec->getCategoryDescription().getCategory());
}
