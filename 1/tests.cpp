#include <gtest/gtest.h>
#include "eliminate_unset_bits.h"

TEST(EliminateUnsetBitsTest, BasicTest1) {
    std::string input = "1101010101010101";
    long result = eliminate_unset_bits(input);
    EXPECT_EQ(result, 255);
}

TEST(EliminateUnsetBitsTest, BasicTest2) {
    std::string input = "111";
    long result = eliminate_unset_bits(input);
    EXPECT_EQ(result, 7);
}

TEST(EliminateUnsetBitsTest, BasicTest3) {
    std::string input = "1000000";
    long result = eliminate_unset_bits(input);
    EXPECT_EQ(result, 1);
}

TEST(EliminateUnsetBitsTest, BasicTest4) {
    std::string input = "000";
    long result = eliminate_unset_bits(input);
    EXPECT_EQ(result, 0);
}

TEST(EliminateUnsetBitsTest, EmptyString) {
    std::string input = "";
    long result = eliminate_unset_bits(input);
    EXPECT_EQ(result, 0);
}

TEST(EliminateUnsetBitsTest, AllOnes) {
    std::string input = "11111";
    long result = eliminate_unset_bits(input);
    EXPECT_EQ(result, 31);
}

TEST(EliminateUnsetBitsTest, AllZeros) {
    std::string input = "0000000";
    long result = eliminate_unset_bits(input);
    EXPECT_EQ(result, 0);
}

TEST(EliminateUnsetBitsTest, InvalidInput) {
    std::string input = "1234567";
    EXPECT_THROW(eliminate_unset_bits(input), std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}