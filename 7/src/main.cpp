#include "gamemanager.h"
#include "game_engine.h"
#include <random>
#include <iostream>

int main() {
    GameManager game;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> pos_dist(0, 99);
    std::uniform_int_distribution<> type_dist(0, 2);
    
    const std::string types[] = {"Knight", "Druid", "Elf"};
    
    std::cout << "Создание NPC:\n";
    for (int i = 0; i < 50; ++i) {
        std::string type = types[type_dist(gen)];
        std::string name = type + std::to_string(i);
        int x = pos_dist(gen);
        int y = pos_dist(gen);
        std::cout << "Создан " << type << " в позиции (" << x << "," << y << ")\n";
        game.addNPC(type, name, x, y);
    }
    std::cout << "NPC созданы. Запуск игры...\n\n";
    
    GameEngine engine(game);
    engine.start();
    
    return 0;
} 