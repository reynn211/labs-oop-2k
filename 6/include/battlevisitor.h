#pragma once
#include "npc.h"
#include "observer.h"
#include <vector>
#include <memory>

class BattleVisitor {
private:
    double battleRange;
    std::vector<BattleObserver*> observers;

public:
    explicit BattleVisitor(double range);
    void addObserver(BattleObserver* observer);
    void removeObserver(BattleObserver* observer);
    
    void notifyObservers(const std::string& message);
    bool processBattle(std::vector<std::shared_ptr<NPC>>& npcs);
}; 