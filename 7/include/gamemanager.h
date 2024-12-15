#pragma once
#include "npc.h"
#include "factory.h"
#include "battlevisitor.h"
#include "observer.h"
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <mutex>
#include <shared_mutex>

class GameManager {
private:
    mutable std::shared_mutex npcs_mutex;
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
    
    std::vector<std::shared_ptr<NPC>>& getNPCs() { 
        return npcs; 
    }
    
    const std::vector<std::shared_ptr<NPC>>& getNPCs() const { 
        return npcs; 
    }
    
    BattleVisitor& getBattleVisitor() { 
        return *battleVisitor; 
    }
}; 