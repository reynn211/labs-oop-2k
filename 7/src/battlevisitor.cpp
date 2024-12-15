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