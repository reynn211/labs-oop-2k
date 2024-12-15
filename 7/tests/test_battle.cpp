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
    GameManager game;
    game.addNPC("Knight", "Knight1", 0, 0);
    game.addNPC("Elf", "Elf1", 0, 0);
    
    auto testObserver = std::make_shared<TestObserver>();
    game.getBattleVisitor().addObserver(testObserver.get());
    
    auto& npcs = game.getNPCs();
    if (npcs[0]->attack(*npcs[1])) {
        npcs[1]->kill();
        std::stringstream message;
        message << npcs[0]->getType() << " " << npcs[0]->getName() 
               << " убил " << npcs[1]->getType() << " " << npcs[1]->getName();
        game.getBattleVisitor().notifyObservers(message.str());
    }
    
    EXPECT_FALSE(npcs[1]->isAlive());
    EXPECT_EQ(testObserver->messages.size(), 1);
}

TEST(BattleTest, OutOfRange) {
    GameManager game;
    game.addNPC("Knight", "Knight1", 0, 0);
    game.addNPC("Elf", "Elf1", 99, 99);
    
    auto& npcs = game.getNPCs();
    EXPECT_GT(npcs[0]->distanceTo(*npcs[1]), npcs[0]->getKillDistance());
    EXPECT_TRUE(npcs[0]->isAlive() && npcs[1]->isAlive());
}

TEST(BattleTest, DruidVsDruid) {
    GameManager game;
    game.addNPC("Druid", "Druid1", 0, 0);
    game.addNPC("Druid", "Druid2", 5, 5);
    
    auto& npcs = game.getNPCs();
    EXPECT_TRUE(npcs[0]->attack(*npcs[1]));
    EXPECT_TRUE(npcs[1]->attack(*npcs[0]));
}