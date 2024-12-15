#include "gamemanager.h"
#include "game_constants.h"
#include <fstream>
#include <iostream>

GameManager::GameManager() {
    factories["Knight"] = std::make_unique<KnightFactory>();
    factories["Druid"] = std::make_unique<DruidFactory>();
    factories["Elf"] = std::make_unique<ElfFactory>();
    
    battleVisitor = std::make_unique<BattleVisitor>(0);
    consoleObserver = std::make_unique<ConsoleObserver>();
    fileObserver = std::make_unique<FileObserver>();
    
    battleVisitor->addObserver(consoleObserver.get());
    battleVisitor->addObserver(fileObserver.get());
}

void GameManager::addNPC(const std::string& type, const std::string& name, int x, int y) {
    if (x < 0 || x >= game_constants::MAP_SIZE || y < 0 || y >= game_constants::MAP_SIZE) {
        throw std::runtime_error("Координаты вне границ");
    }
    
    auto factory = factories.find(type);
    if (factory != factories.end()) {
        npcs.push_back(factory->second->createNPC(name, x, y));
    }
}

void GameManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& npc : npcs) {
        file << npc->getType() << " " << npc->getName() << " " 
             << npc->getX() << " " << npc->getY() << "\n";
    }
}

void GameManager::loadFromFile(const std::string& filename) {
    npcs.clear();
    std::ifstream file(filename);
    std::string type, name;
    int x, y;
    
    while (file >> type >> name >> x >> y) {
        addNPC(type, name, x, y);
    }
}

void GameManager::printNPCs() const {
    for (const auto& npc : npcs) {
        std::cout << npc->getType() << " " << npc->getName() 
                 << " в (" << npc->getX() << "," << npc->getY() << ")\n";
    }
}