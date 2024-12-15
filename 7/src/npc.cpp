#include "npc.h"
#include "game_constants.h"
#include <cmath>
#include <random>
#include <iostream>

NPC::NPC(const std::string& name, int x, int y) 
    : name(name), x(x), y(y), alive(true) {}

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

void NPC::move() {
    if (!alive) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> angle_dist(0, 359);
    
    double angle = angle_dist(gen) * M_PI / 180.0;
    int distance = getMoveDistance();
    
    int new_x = x + static_cast<int>(distance * cos(angle));
    int new_y = y + static_cast<int>(distance * sin(angle));
    
    x = std::max(0, std::min(new_x, game_constants::MAP_SIZE - 1));
    y = std::max(0, std::min(new_y, game_constants::MAP_SIZE - 1));
}

int NPC::rollDice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);
    return dist(gen);
} 