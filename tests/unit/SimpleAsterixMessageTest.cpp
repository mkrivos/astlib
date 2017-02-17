///
/// \package astlib
/// \file SimpleAsterixMessageTest.cpp
///
/// \author Marian Krivos <marian.krivos@rsys.sk>
/// \date 31Jan.,2017 
/// \brief definicia typu
///
/// (C) Copyright 2017 R-SYS s.r.o
/// All rights reserved.
///

#include "astlib/decoder/SimpleAsterixMessage.h"
#include "gtest/gtest.h"

using namespace astlib;

class SimpleAsterixMessageTest:
    public testing::Test
{
public:
    SimpleAsterixMessageTest()
    {
    }
};

using namespace astlib;

TEST_F(SimpleAsterixMessageTest, basic)
{
    SimpleAsterixMessage msg;
    EXPECT_EQ(0, msg.size());

    msg.addSimpleItem(0x01000001, "jano");
    EXPECT_EQ(1, msg.size());
    msg.addSimpleItem(0x01000001, "jano");
    EXPECT_EQ(1, msg.size());
    msg.addSimpleItem(0x01000002, "jano");
    EXPECT_EQ(2, msg.size());
    msg.clear();
    EXPECT_EQ(0, msg.size());
}

TEST_F(SimpleAsterixMessageTest, booleanValue)
{
    SimpleAsterixMessage msg;

    EXPECT_FALSE(msg.hasItem(0x01000001));
    msg.addSimpleItem(0x01000001, true);
    EXPECT_TRUE(msg.hasItem(0x01000001));

    bool value = false;
    EXPECT_TRUE(msg.getBoolean(0x01000001, value));
    EXPECT_EQ(true, value);
}

TEST_F(SimpleAsterixMessageTest, signedValue)
{
    SimpleAsterixMessage msg;

    EXPECT_FALSE(msg.hasItem(0x02000002));
    msg.addSimpleItem(0x02000002, Poco::Int64(-5782396523467L));
    EXPECT_TRUE(msg.hasItem(0x02000002));

    Poco::Int64 value = 0;
    EXPECT_TRUE(msg.getSigned(0x02000002, value));
    EXPECT_EQ(Poco::Int64(-5782396523467L), value);
}

TEST_F(SimpleAsterixMessageTest, realValue)
{
    SimpleAsterixMessage msg;

    EXPECT_FALSE(msg.hasItem(0x04000003));
    msg.addSimpleItem(0x04000003, -5782396527.0);
    EXPECT_TRUE(msg.hasItem(0x04000003));

    double value = 0;
    EXPECT_TRUE(msg.getReal(0x04000003, value));
    EXPECT_EQ(-5782396527.0, value);
}

TEST_F(SimpleAsterixMessageTest, stringValue)
{
    SimpleAsterixMessage msg;

    EXPECT_FALSE(msg.hasItem(0x05000004));
    msg.addSimpleItem(0x05000004, "fgsdhajdgf45w35234");
    EXPECT_TRUE(msg.hasItem(0x05000004));

    std::string value = "fgsdhajdgf45w35234";
    EXPECT_TRUE(msg.getString(0x05000004, value));
    EXPECT_EQ("fgsdhajdgf45w35234", value);
}
