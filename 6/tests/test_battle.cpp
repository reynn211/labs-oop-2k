#include <gtest/gtest.h>
#include "battlevisitor.h"
#include "gamemanager.h"

class TestObserver : public BattleObserver {
public:
    std::vector<std::string> messages;
    void onBattleEvent(const std::string& message) override {
        messages.push_back(message);
    }
};

TEST(BattleTest, MutualDestruction) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(std::make_shared<Knight>("Knight1", 0, 0));
    npcs.push_back(std::make_shared<Elf>("Elf1", 0, 0));
    
    auto testObserver = std::make_shared<TestObserver>();
    BattleVisitor visitor(100);
    visitor.addObserver(testObserver.get());
    
    visitor.processBattle(npcs);
    
    EXPECT_EQ(npcs.size(), 0);
    EXPECT_EQ(testObserver->messages.size(), 2);
}

TEST(BattleTest, OutOfRange) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(std::make_shared<Knight>("Knight1", 0, 0));
    npcs.push_back(std::make_shared<Elf>("Elf1", 1000, 1000));
    
    BattleVisitor visitor(100);
    visitor.processBattle(npcs);
    
    EXPECT_EQ(npcs.size(), 2);
}

TEST(BattleTest, DruidVsDruid) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(std::make_shared<Druid>("Druid1", 0, 0));
    npcs.push_back(std::make_shared<Druid>("Druid2", 0, 0));
    
    BattleVisitor visitor(100);
    visitor.processBattle(npcs);
    
    EXPECT_EQ(npcs.size(), 0);
} 