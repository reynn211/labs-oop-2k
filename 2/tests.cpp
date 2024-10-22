#include <gtest/gtest.h>
#include "bitstring.h"
#include <iostream>

inline BitString BS(const char* str) {
    return BitString(reinterpret_cast<const unsigned char*>(str));
}

TEST(BitStringTest, DefaultConstructor) {
    BitString bs;
    EXPECT_EQ(bs.size(), 1);
}

TEST(BitStringTest, StringConstructor) {
    BitString bs = BS("10110");
    EXPECT_EQ(bs.size(), 5);
    EXPECT_EQ(bs.get(0), '1');
    EXPECT_EQ(bs.get(1), '0');
    EXPECT_EQ(bs.get(2), '1');
    EXPECT_EQ(bs.get(3), '1');
    EXPECT_EQ(bs.get(4), '0');
}

TEST(BitStringTest, CopyConstructor) {
    BitString bs1 = BS("10110");
    BitString bs2(bs1);
    EXPECT_EQ(bs1.size(), bs2.size());
    for (size_t i = 0; i < bs1.size(); ++i) {
        EXPECT_EQ(bs1.get(i), bs2.get(i));
    }
}

TEST(BitStringTest, MoveConstructor) {
    BitString bs1 = BS("10110");
    BitString bs2(std::move(bs1));
    EXPECT_EQ(bs2.size(), 5);
    EXPECT_EQ(bs2.get(0), '1');
    EXPECT_EQ(bs2.get(1), '0');
    EXPECT_EQ(bs2.get(2), '1');
    EXPECT_EQ(bs2.get(3), '1');
    EXPECT_EQ(bs2.get(4), '0');
    EXPECT_EQ(bs1.size(), 0);
}

TEST(BitStringTest, Addition) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("1101");
    BitString result = bs1 + bs2;
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result.get(0), '1');
    EXPECT_EQ(result.get(1), '1');
    EXPECT_EQ(result.get(2), '0');
    EXPECT_EQ(result.get(3), '0');
    EXPECT_EQ(result.get(4), '0');
}

TEST(BitStringTest, Subtraction) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("0011");
    BitString result = bs1 - bs2;
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result.get(0), '1');
    EXPECT_EQ(result.get(1), '0');
    EXPECT_EQ(result.get(2), '0');
    EXPECT_EQ(result.get(3), '0');
}

TEST(BitStringTest, AdditionAssignment) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("1101");
    bs1 += bs2;
    EXPECT_EQ(bs1.size(), 5);
    EXPECT_EQ(bs1.get(0), '1');
    EXPECT_EQ(bs1.get(1), '1');
    EXPECT_EQ(bs1.get(2), '0');
    EXPECT_EQ(bs1.get(3), '0');
    EXPECT_EQ(bs1.get(4), '0');
}

TEST(BitStringTest, SubtractionAssignment) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("0011");
    bs1 -= bs2;
    EXPECT_EQ(bs1.size(), 4);
    EXPECT_EQ(bs1.get(0), '1');
    EXPECT_EQ(bs1.get(1), '0');
    EXPECT_EQ(bs1.get(2), '0');
    EXPECT_EQ(bs1.get(3), '0');
}

TEST(BitStringTest, GreaterThan) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("1010");
    EXPECT_TRUE(bs1 > bs2);
    EXPECT_FALSE(bs2 > bs1);
}

TEST(BitStringTest, LessThan) {
    BitString bs1 = BS("1010");
    BitString bs2 = BS("1011");
    EXPECT_TRUE(bs1 < bs2);
    EXPECT_FALSE(bs2 < bs1);
}

TEST(BitStringTest, EqualTo) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("1011");
    BitString bs3 = BS("1010");
    EXPECT_TRUE(bs1 == bs2);
    EXPECT_FALSE(bs1 == bs3);
}

TEST(BitStringTest, SetAndGet) {
    BitString bs = BS("00000");
    bs.set(2, '1');
    EXPECT_EQ(bs.get(2), '1');
    EXPECT_EQ(bs.get(0), '0');
    EXPECT_THROW(bs.get(5), std::out_of_range);
    EXPECT_THROW(bs.set(5, '1'), std::out_of_range);
}

TEST(BitStringTest, BitwiseAND) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("1101");
    BitString result = bs1 & bs2;
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result.get(0), '1');
    EXPECT_EQ(result.get(1), '0');
    EXPECT_EQ(result.get(2), '0');
    EXPECT_EQ(result.get(3), '1');
}

TEST(BitStringTest, BitwiseOR) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("1101");
    BitString result = bs1 | bs2;
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result.get(0), '1');
    EXPECT_EQ(result.get(1), '1');
    EXPECT_EQ(result.get(2), '1');
    EXPECT_EQ(result.get(3), '1');
}

TEST(BitStringTest, BitwiseXOR) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("1101");
    BitString result = bs1 ^ bs2;
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result.get(0), '0');
    EXPECT_EQ(result.get(1), '1');
    EXPECT_EQ(result.get(2), '1');
    EXPECT_EQ(result.get(3), '0');
}

TEST(BitStringTest, BitwiseNOT) {
    BitString bs = BS("1011");
    BitString result = ~bs;
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result.get(0), '0');
    EXPECT_EQ(result.get(1), '1');
    EXPECT_EQ(result.get(2), '0');
    EXPECT_EQ(result.get(3), '0');
}

TEST(BitStringTest, CopyAssignment) {
    BitString bs1 = BS("1011");
    BitString bs2;
    bs2 = bs1;
    EXPECT_EQ(bs1.size(), bs2.size());
    for (size_t i = 0; i < bs1.size(); ++i) {
        EXPECT_EQ(bs1.get(i), bs2.get(i));
    }
}

TEST(BitStringTest, MoveAssignment) {
    BitString bs1 = BS("1011");
    BitString bs2;
    bs2 = std::move(bs1);
    EXPECT_EQ(bs2.size(), 4);
    EXPECT_EQ(bs2.get(0), '1');
    EXPECT_EQ(bs2.get(1), '0');
    EXPECT_EQ(bs2.get(2), '1');
    EXPECT_EQ(bs2.get(3), '1');
    EXPECT_EQ(bs1.size(), 0);
}

TEST(BitStringTest, InvalidStringConstructor) {
    EXPECT_THROW(BS("10110a"), std::invalid_argument);
}

TEST(BitStringTest, SubtractionWithNegativeResult) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("1101");
    EXPECT_THROW(bs1 - bs2, std::runtime_error);
}

TEST(BitStringTest, AdditionWithCarry) {
    BitString bs1 = BS("1111");
    BitString bs2 = BS("0001");
    BitString result = bs1 + bs2;
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result.get(0), '1');
    EXPECT_EQ(result.get(1), '0');
    EXPECT_EQ(result.get(2), '0');
    EXPECT_EQ(result.get(3), '0');
    EXPECT_EQ(result.get(4), '0');
}

TEST(BitStringTest, BitwiseAndWithDifferentLengths) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("11");
    
    BitString andResult = bs1 & bs2;
    EXPECT_EQ(andResult.size(), 2);
    EXPECT_EQ(andResult.get(0), '1');
    EXPECT_EQ(andResult.get(1), '1');
}

TEST(BitStringTest, BitwiseOrWithDifferentLengths) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("11");

    BitString orResult = bs1 | bs2;
    EXPECT_EQ(orResult.size(), 4);
    EXPECT_EQ(orResult.get(0), '1');
    EXPECT_EQ(orResult.get(1), '0');
    EXPECT_EQ(orResult.get(2), '1');
    EXPECT_EQ(orResult.get(3), '1');
}

TEST(BitStringTest, BitwiseXorWithDifferentLengths) {
    BitString bs1 = BS("1011");
    BitString bs2 = BS("11");

    BitString xorResult = bs1 ^ bs2;
    EXPECT_EQ(xorResult.size(), 4);
    EXPECT_EQ(xorResult.get(0), '1');
    EXPECT_EQ(xorResult.get(1), '0');
    EXPECT_EQ(xorResult.get(2), '0');
    EXPECT_EQ(xorResult.get(3), '0');
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
