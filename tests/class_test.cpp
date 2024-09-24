#include "money.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST(MoneyTest, DefaultConstructor) {
    Money m;
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "0.00");
}

TEST(MoneyTest, InitializerListConstructor) {
    Money m = {1, 2, 3};
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "3.21");
}

TEST(MoneyTest, StringConstructor) {
    Money m1("12345");
    std::stringstream ss1;
    ss1 << m1;
    EXPECT_EQ(ss1.str(), "123.45");

    Money m2("0012345");
    std::stringstream ss2;
    ss2 << m2;
    EXPECT_EQ(ss2.str(), "123.45");

    Money m3("123.45");
    std::stringstream ss3;
    ss3 << m3;
    EXPECT_EQ(ss3.str(), "123.45");

    EXPECT_TRUE(m1 == m2);
    EXPECT_TRUE(m1 == m3);
}

TEST(MoneyTest, CopyConstructor) {
    Money m1("12345");
    Money m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(MoneyTest, MoveConstructor) {
    Money m1("12345");
    Money m2(std::move(m1));
    std::stringstream ss;
    ss << m2;
    EXPECT_EQ(ss.str(), "123.45");
}

TEST(MoneyTest, CopyAssignment) {
    Money m1("12345");
    Money m2;
    m2 = m1;
    EXPECT_TRUE(m1 == m2);
}

TEST(MoneyTest, MoveAssignment) {
    Money m1("12345");
    Money m2;
    m2 = std::move(m1);
    std::stringstream ss;
    ss << m2;
    EXPECT_EQ(ss.str(), "123.45");
}

TEST(MoneyTest, ComparisonOperators) {
    Money m1("10000"); // 100.00
    Money m2("20000"); // 200.00
    Money m3("10000"); // 100.00

    EXPECT_TRUE(m1 == m3);
    EXPECT_FALSE(m1 == m2);

    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 != m3);

    EXPECT_TRUE(m1 < m2);
    EXPECT_FALSE(m2 < m1);
    EXPECT_FALSE(m1 < m3);

    EXPECT_TRUE(m2 > m1);
    EXPECT_FALSE(m1 > m2);
    EXPECT_FALSE(m1 > m3);

    EXPECT_TRUE(m1 <= m2);
    EXPECT_TRUE(m1 <= m3);
    EXPECT_FALSE(m2 <= m1);

    EXPECT_TRUE(m2 >= m1);
    EXPECT_TRUE(m1 >= m3);
    EXPECT_FALSE(m1 >= m2);
}

TEST(MoneyTest, AdditionOperator) {
    Money m1("10050"); // 100.50
    Money m2("20025"); // 200.25
    Money result = m1 + m2;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "300.75");

    m1 += m2;
    std::stringstream ss2;
    ss2 << m1;
    EXPECT_EQ(ss2.str(), "300.75");
}

TEST(MoneyTest, SubtractionOperator) {
    Money m1("20050"); // 200.50
    Money m2("10025"); // 100.25
    Money result = m1 - m2;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "100.25");

    m1 -= m2;
    std::stringstream ss2;
    ss2 << m1;
    EXPECT_EQ(ss2.str(), "100.25");
}

TEST(MoneyTest, SubtractionToZero) {
    Money m1("10000"); // 100.00
    Money m2("10000"); // 100.00
    Money result = m1 - m2;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "0.00");

    m1 -= m2;
    std::stringstream ss2;
    ss2 << m1;
    EXPECT_EQ(ss2.str(), "0.00");
}

TEST(MoneyTest, SubtractionNegativeResult) {
    Money m1("10000"); // 100.00
    Money m2("20000"); // 200.00
    EXPECT_THROW(Money result = m1 - m2, std::invalid_argument);
    EXPECT_THROW(m1 -= m2, std::invalid_argument);
}

TEST(MoneyTest, OutputOperator) {
    Money m("12345"); // 123.45
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "123.45");
}

TEST(MoneyTest, LargeNumbers) {
    Money m1("1234567890123456789012"); // 12345678901234567.89012
    Money m2("98765432109876543210988"); // 98765432109876543.210988
    Money sum = m1 + m2;
    std::stringstream ss;
    ss << sum;
    EXPECT_EQ(ss.str(), "1000000000000000000000.00");
}

TEST(MoneyTest, ZeroValue) {
    Money m("0");
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "0.00");

    Money m1("0");
    Money m2("0");
    Money sum = m1 + m2;
    std::stringstream ss2;
    ss2 << sum;
    EXPECT_EQ(ss2.str(), "0.00");
}

TEST(MoneyTest, Normalization) {
    Money m("000012345"); // 123.45
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "123.45");

}

TEST(MoneyTest, AdditionWithCarry) {
    Money m1("99999"); // 999.99
    Money m2("1");     // 0.01
    Money result = m1 + m2;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "1000.00");
}

TEST(MoneyTest, SubtractionWithBorrow) {
    Money m1("10000"); // 100.00
    Money m2("1");     // 0.01
    Money result = m1 - m2;
    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "99.99");
}

TEST(MoneyTest, MinimalValue) {
    Money m("1"); // 0.01
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "0.01");
}

TEST(MoneyTest, EmptyStringConstructor) {
    Money m("");
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "0.00");
}

TEST(MoneyTest, InvalidCharacters) {

    EXPECT_THROW(Money m("1a2b3c"), std::invalid_argument);
}

TEST(MoneyTest, SelfAssignment) {
    Money m("12345"); // 123.45
    m = m;
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "123.45");
}

TEST(MoneyTest, SelfMoveAssignment) {
    Money m("12345"); // 123.45
    m = std::move(m);
    std::stringstream ss;
    ss << m;
    EXPECT_EQ(ss.str(), "123.45");
}
