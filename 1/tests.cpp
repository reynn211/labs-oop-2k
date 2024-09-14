#include <gtest/gtest.h>
#include "eliminate_unset_bits.h"

TEST(EliminateUnsetBitsTest, BasicTests) {
    EXPECT_EQ(eliminate_unset_bits("1101010101010101"), 255);
    EXPECT_EQ(eliminate_unset_bits("111"), 7);
    EXPECT_EQ(eliminate_unset_bits("1000000"), 1);
    EXPECT_EQ(eliminate_unset_bits("000"), 0);
}

TEST(EliminateUnsetBitsTest, EmptyString) {
    EXPECT_EQ(eliminate_unset_bits(""), 0);
}

TEST(EliminateUnsetBitsTest, AllOnes) {
    EXPECT_EQ(eliminate_unset_bits("11111"), 31);
}

TEST(EliminateUnsetBitsTest, AllZeros) {
    EXPECT_EQ(eliminate_unset_bits("0000000"), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}