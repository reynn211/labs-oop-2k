#include <gtest/gtest.h>
#include "npc.h"

TEST(NPCTest, Distance) {
    Knight knight("Knight1", 0, 0);
    Elf elf("Elf1", 3, 4);
    
    EXPECT_DOUBLE_EQ(knight.distanceTo(elf), 5.0);
    EXPECT_DOUBLE_EQ(elf.distanceTo(knight), 5.0);
}

TEST(NPCTest, KnightAttacks) {
    Knight knight("Knight1", 0, 0);
    Elf elf("Elf1", 0, 0);
    Druid druid("Druid1", 0, 0);
    
    EXPECT_TRUE(knight.attack(elf));
    EXPECT_FALSE(knight.attack(druid));
}

TEST(NPCTest, ElfAttacks) {
    Elf elf("Elf1", 0, 0);
    Knight knight("Knight1", 0, 0);
    Druid druid("Druid1", 0, 0);
    
    EXPECT_TRUE(elf.attack(knight));
    EXPECT_TRUE(elf.attack(druid));
}

TEST(NPCTest, DruidAttacks) {
    Druid druid1("Druid1", 0, 0);
    Druid druid2("Druid2", 0, 0);
    Knight knight("Knight1", 0, 0);
    
    EXPECT_TRUE(druid1.attack(druid2));
    EXPECT_FALSE(druid1.attack(knight));
} 