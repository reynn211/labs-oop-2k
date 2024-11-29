#include "npc.h"
#include <cmath>

NPC::NPC(const std::string& name, int x, int y) 
    : name(name), x(x), y(y) {}

double NPC::distanceTo(const NPC& other) const {
    int dx = x - other.x;
    int dy = y - other.y;
    return std::sqrt(dx*dx + dy*dy);
}

Knight::Knight(const std::string& name, int x, int y) 
    : NPC(name, x, y) { type = "Knight"; }

bool Knight::attack(NPC& other) {
    return other.getType() == "Elf";
}

Druid::Druid(const std::string& name, int x, int y) 
    : NPC(name, x, y) { type = "Druid"; }

bool Druid::attack(NPC& other) {
    return other.getType() == "Druid";
}

Elf::Elf(const std::string& name, int x, int y) 
    : NPC(name, x, y) { type = "Elf"; }

bool Elf::attack(NPC& other) {
    return other.getType() == "Knight" || other.getType() == "Druid";
} 