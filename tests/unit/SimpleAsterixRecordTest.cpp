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

#include "astlib/SimpleAsterixRecord.h"
#include "astlib/AsterixItemDictionary.h"

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
    SimpleAsterixRecord msg;
    EXPECT_EQ(0, msg.size());

    msg.setItem(0x01000001, "jano");
    EXPECT_EQ(1, msg.size());
    msg.setItem(0x01000001, "jano");
    EXPECT_EQ(1, msg.size());
    msg.setItem(0x01000002, "jano");
    EXPECT_EQ(2, msg.size());
    msg.clear();
    EXPECT_EQ(0, msg.size());
}

TEST_F(SimpleAsterixMessageTest, booleanValue)
{
    SimpleAsterixRecord msg;

    EXPECT_FALSE(msg.hasItem(0x01000001));
    msg.setItem(0x01000001, true);
    EXPECT_TRUE(msg.hasItem(0x01000001));

    bool value = false;
    EXPECT_TRUE(msg.getBoolean(0x01000001, value));
    EXPECT_EQ(true, value);
}

TEST_F(SimpleAsterixMessageTest, signedValue)
{
    SimpleAsterixRecord msg;

    EXPECT_FALSE(msg.hasItem(0x02000002));
    msg.setItem(0x02000002, Poco::Int64(-5782396523467L));
    EXPECT_TRUE(msg.hasItem(0x02000002));

    Poco::Int64 value = 0;
    EXPECT_TRUE(msg.getSigned(0x02000002, value));
    EXPECT_EQ(Poco::Int64(-5782396523467L), value);
}

TEST_F(SimpleAsterixMessageTest, realValue)
{
    SimpleAsterixRecord msg;

    EXPECT_FALSE(msg.hasItem(0x04000003));
    msg.setItem(0x04000003, -5782396527.0);
    EXPECT_TRUE(msg.hasItem(0x04000003));

    double value = 0;
    EXPECT_TRUE(msg.getReal(0x04000003, value));
    EXPECT_EQ(-5782396527.0, value);
}

TEST_F(SimpleAsterixMessageTest, stringValue)
{
    SimpleAsterixRecord msg;

    EXPECT_FALSE(msg.hasItem(0x05000004));
    msg.setItem(0x05000004, "fgsdhajdgf45w35234");
    EXPECT_TRUE(msg.hasItem(0x05000004));

    std::string value = "fgsdhajdgf45w35234";
    EXPECT_TRUE(msg.getString(0x05000004, value));
    EXPECT_EQ("fgsdhajdgf45w35234", value);
}

TEST_F(SimpleAsterixMessageTest, array)
{
    SimpleAsterixRecord msg;
    AsterixItemCode code(1, 2, true);
    Poco::Int64 value = 0;

    msg.initializeArray(code, 2);
    msg.setItem(code, 42, 0);
    msg.setItem(code, 43, 1);
    EXPECT_EQ(1, msg.size());
    EXPECT_TRUE(code.isArray());
    EXPECT_TRUE(msg.hasItem(code));
    EXPECT_TRUE(msg.getSigned(code, value, 0));
    EXPECT_EQ(42, value);
    EXPECT_TRUE(msg.getSigned(code, value, 1));
    EXPECT_EQ(43, value);

    std::cout << msg.toString() << std::endl;
}

TEST_F(SimpleAsterixMessageTest, toString)
{
    SimpleAsterixRecord msg;
    double value = 0;

    msg.initializeArray(TRAJECTORY_INTENT_TCP_LATITUDE, 2);
    msg.setItem(TRAJECTORY_INTENT_TCP_LATITUDE, 42.67, 0);
    msg.setItem(TRAJECTORY_INTENT_TCP_LATITUDE, -64542.7, 1);

    EXPECT_TRUE(msg.hasItem(TRAJECTORY_INTENT_TCP_LATITUDE));
    EXPECT_TRUE(msg.getReal(TRAJECTORY_INTENT_TCP_LATITUDE, value, 0));
    EXPECT_EQ(42.67, value);
    EXPECT_TRUE(msg.getReal(TRAJECTORY_INTENT_TCP_LATITUDE, value, 1));
    EXPECT_EQ(-64542.7, value);
}

TEST_F(SimpleAsterixMessageTest, fromToJson)
{
    SimpleAsterixRecord msg;

    msg.setItem(SYSTEM_STATUS_NOGO, true);
    msg.setItem(DSI_SAC, 100);
    msg.setItem(DSI_SIC, 200);
    msg.setItem(TRACK_DOPPLER_CALCULATION, -11111);
    msg.setItem(TIMEOFDAY, 2000.10);
    msg.setItem(TARGET_ADDRESS, "JANO44 342");

    msg.initializeArray(TRAJECTORY_INTENT_TCP_LATITUDE, 2);
    msg.setItem(TRAJECTORY_INTENT_TCP_LATITUDE, 42.67, 0);
    msg.setItem(TRAJECTORY_INTENT_TCP_LATITUDE, -64542.7, 1);

    std::string json = msg.toJson();
    //std::cout << json << std::endl;
    EXPECT_EQ(192, json.size());

    SimpleAsterixRecordPtr msg2 = SimpleAsterixRecord::fromJson(json);
    std::string json2 = msg2->toJson();
    //std::cout << json2 << std::endl;
    EXPECT_EQ(192, json2.size());

}
