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
#include "astlib/specifications/entries.h"
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
    CodecDeclarationLoader loader(true);
    std::istringstream stream(std::string(astlib::cat048_1_21));
    CodecDescriptionPtr codecSpecification = loader.parse(stream);
    ASSERT_TRUE(codecSpecification.get());

    // Header
    const CategoryDescription& catDesc = codecSpecification->getCategoryDescription();
    EXPECT_EQ(48, catDesc.getCategory());
    EXPECT_EQ(AsterixVersion(1,21), catDesc.getEdition());
    EXPECT_EQ(AsterixFamily(AsterixFamily::Eurocontrol), catDesc.getFamily());

    // Uap
    const CodecDescription::UapItems& uap = codecSpecification->enumerateUapItems();
    EXPECT_EQ(28, uap.size());

    // Data items
    const CodecDescription::ItemDescriptionTable& dataItems = codecSpecification->enumerateDataItems();
    EXPECT_EQ(28, dataItems.size());
}

TEST_F( CodecDeclarationLoaderTest, loadCat62Asterixed)
{
    CodecDeclarationLoader loader;
    std::istringstream stream(std::string(astlib::cat062_1_16));
    CodecDescriptionPtr codecSpecification = loader.parse(stream);
    ASSERT_TRUE(codecSpecification.get());

    // Header
    const CategoryDescription& catDesc = codecSpecification->getCategoryDescription();
    EXPECT_EQ(62, catDesc.getCategory());
    EXPECT_EQ(AsterixVersion(1,16), catDesc.getEdition());
    EXPECT_EQ(AsterixFamily(AsterixFamily::Eurocontrol), catDesc.getFamily());

    // Uap
    const CodecDescription::UapItems& uap = codecSpecification->enumerateUapItems();
    EXPECT_EQ(35, uap.size());

    // Data items
    const CodecDescription::ItemDescriptionTable& dataItems = codecSpecification->enumerateDataItems();
    EXPECT_EQ(30, dataItems.size());
}
