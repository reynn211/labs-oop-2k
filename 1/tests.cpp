#include <gtest/gtest.h>
#include "eliminate_unset_bits.h"

TEST(EliminateUnsetBitsTest, BasicTests) {
    std::string input1 = "1101010101010101";
    std::string input2 = "111";
    std::string input3 = "1000000";
    std::string input4 = "000";

    long result1 = eliminate_unset_bits(input1);
    long result2 = eliminate_unset_bits(input2);
    long result3 = eliminate_unset_bits(input3);
    long result4 = eliminate_unset_bits(input4);

    EXPECT_EQ(result1, 255);
    EXPECT_EQ(result2, 7);
    EXPECT_EQ(result3, 1);
    EXPECT_EQ(result4, 0);
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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}