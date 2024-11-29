#include "battlevisitor.h"
#include <algorithm>
#include <set>

BattleVisitor::BattleVisitor(double range) : battleRange(range) {}

void BattleVisitor::addObserver(BattleObserver* observer) {
    observers.push_back(observer);
}

void BattleVisitor::removeObserver(BattleObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void BattleVisitor::notifyObservers(const std::string& message) {
    for (auto observer : observers) {
        observer->onBattleEvent(message);
    }
}

bool BattleVisitor::processBattle(std::vector<std::shared_ptr<NPC>>& npcs) {
    bool hadBattle = false;
    std::set<size_t> toRemove;
    
    struct Attack {
        size_t attacker;
        size_t target;
        std::string attackerName;
        std::string attackerType;
        std::string targetName;
        std::string targetType;
    };
    std::vector<Attack> successfulAttacks;
    
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = 0; j < npcs.size(); ++j) {
            if (i != j && npcs[i]->distanceTo(*npcs[j]) <= battleRange) {
                if (npcs[i]->attack(*npcs[j])) {
                    successfulAttacks.push_back({
                        i, j,
                        npcs[i]->getName(),
                        npcs[i]->getType(),
                        npcs[j]->getName(),
                        npcs[j]->getType()
                    });
                    hadBattle = true;
                }
            }
        }
    }
    
    for (const auto& attack : successfulAttacks) {
        toRemove.insert(attack.target);
        notifyObservers(attack.attackerType + " " + attack.attackerName + 
                       " убивает " + attack.targetType + " " + attack.targetName);
    }
    
    for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) {
        npcs.erase(npcs.begin() + *it);
    }
    
    return hadBattle;
} 