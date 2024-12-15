#include <gtest/gtest.h>
#include "factory.h"

TEST(FactoryTest, CreateKnight) {
    KnightFactory factory;
    auto knight = factory.createNPC("TestKnight", 100, 200);
    
    EXPECT_EQ(knight->getName(), "TestKnight");
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(knight->getX(), 100);
    EXPECT_EQ(knight->getY(), 200);
}

TEST(FactoryTest, CreateDruid) {
    DruidFactory factory;
    auto druid = factory.createNPC("TestDruid", 300, 400);
    
    EXPECT_EQ(druid->getName(), "TestDruid");
    EXPECT_EQ(druid->getType(), "Druid");
    EXPECT_EQ(druid->getX(), 300);
    EXPECT_EQ(druid->getY(), 400);
}

TEST(FactoryTest, CreateElf) {
    ElfFactory factory;
    auto elf = factory.createNPC("TestElf", 50, 50);
    
    EXPECT_EQ(elf->getName(), "TestElf");
    EXPECT_EQ(elf->getType(), "Elf");
    EXPECT_EQ(elf->getX(), 50);
    EXPECT_EQ(elf->getY(), 50);
} 