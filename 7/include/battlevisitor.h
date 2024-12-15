#pragma once
#include "npc.h"
#include "observer.h"
#include <vector>
#include <memory>

class BattleVisitor {
private:
    std::vector<BattleObserver*> observers;
    double battleRange;

public:
    explicit BattleVisitor(double range);
    void addObserver(BattleObserver* observer);
    void removeObserver(BattleObserver* observer);
    void notifyObservers(const std::string& message);
}; 