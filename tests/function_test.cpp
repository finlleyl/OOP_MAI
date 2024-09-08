#include <gtest/gtest.h>
#include <function.h>

TEST(ConvertTo24HourFormatTest, Midnight) {
    int hour = 12;
    int minute = 0;
    std::string period = "AM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "0000");
}

TEST(ConvertTo24HourFormatTest, Noon) {
    int hour = 12;
    int minute = 0;
    std::string period = "PM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "1200");
}

TEST(ConvertTo24HourFormatTest, EarlyMorning) {
    int hour = 1;
    int minute = 30;
    std::string period = "AM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "0130");
}

TEST(ConvertTo24HourFormatTest, LateMorning) {
    int hour = 11;
    int minute = 59;
    std::string period = "AM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "1159");
}

TEST(ConvertTo24HourFormatTest, EarlyAfternoon) {
    int hour = 1;
    int minute = 0;
    std::string period = "PM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "1300");
}

TEST(ConvertTo24HourFormatTest, Evening) {
    int hour = 6;
    int minute = 45;
    std::string period = "PM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "1845");
}

TEST(ConvertTo24HourFormatTest, MorningLeadingZeroes) {
    int hour = 7;
    int minute = 7;
    std::string period = "AM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "0707");
}

TEST(ConvertTo24HourFormatTest, LateNight) {
    int hour = 10;
    int minute = 30;
    std::string period = "PM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "2230");
}

TEST(ConvertTo24HourFormatTest, Morning) {
    int hour = 9;
    int minute = 5;
    std::string period = "AM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "0905");
}

TEST(ConvertTo24HourFormatTest, LateEvening) {
    int hour = 11;
    int minute = 11;
    std::string period = "PM";

    std::string result = convertTo24H(hour, minute, period);

    EXPECT_EQ(result, "2311");
}
