#pragma once
#include "npc.h"
#include "factory.h"
#include "battlevisitor.h"
#include "observer.h"
#include <vector>
#include <memory>
#include <map>

class GameManager {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::map<std::string, std::unique_ptr<NPCFactory>> factories;
    std::unique_ptr<BattleVisitor> battleVisitor;
    std::unique_ptr<ConsoleObserver> consoleObserver;
    std::unique_ptr<FileObserver> fileObserver;

public:
    GameManager();
    
    void addNPC(const std::string& type, const std::string& name, int x, int y);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void printNPCs() const;
    void startBattle(double range);
}; 