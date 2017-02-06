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
    CodecDeclarationLoader loader;
    CodecDescriptionPtr codecSpecification = loader.load("specs/asterix_cat048_1_14.xml");
    ASSERT_TRUE(codecSpecification);

    // Header
    const CategoryDescription& catDesc = codecSpecification->getCategoryDescription();
    EXPECT_EQ(48, catDesc.getCategory());
    EXPECT_EQ(AsterixVersion(1,14), catDesc.getEdition());
    EXPECT_EQ(AsterixFamily(AsterixFamily::Eurocontrol), catDesc.getFamily());

    // Uap
    const CodecDescription::UapItems& uap = codecSpecification->enumerateUapItems();
    EXPECT_EQ(32, uap.size());

    // Data items
    const CodecDescription::ItemDescriptionTable& dataItems = codecSpecification->enumerateDataItems();
    EXPECT_EQ(32, dataItems.size());
}
