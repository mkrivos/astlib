///
/// \package astlib
/// \file CodecDeclarationLoaderTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/CodecDeclarationLoader.h"
#include "gtest/gtest.h"

using namespace astlib;

class CodecDeclarationLoaderTest:
    public testing::Test
{
public:
    CodecDeclarationLoaderTest()
    {
        std::cout << std::fixed << std::setprecision(8);
    }
    ~CodecDeclarationLoaderTest()
    {
    }


public:
    void SetUp()
    {
    }
};

TEST_F( CodecDeclarationLoaderTest, loadCat48Asterixed)
{

}
