#include "coroutine_engine.h"
#include "game_constants.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>

CoroutineEngine::CoroutineEngine(GameManager& game) : game(game) {}

Generator<GameState> CoroutineEngine::processMovements() {
    while (running) {
        auto& npcs = game.getNPCs();
        for (auto& npc : npcs) {
            if (npc->isAlive()) {
                npc->move();
            }
        }
        co_yield GameState{false, true};
    }
    co_yield GameState{false, false};
}

Generator<GameState> CoroutineEngine::processBattles() {
    while (running) {
        bool hadBattle = false;
        std::vector<std::string> battle_messages;
        
        auto& npcs = game.getNPCs();
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!npcs[i]->isAlive() || !npcs[j]->isAlive()) continue;

                if (npcs[i]->distanceTo(*npcs[j]) <= npcs[i]->getKillDistance()) {
                    if (npcs[i]->attack(*npcs[j])) {
                        if (npcs[i]->rollDice() > npcs[j]->rollDice()) {
                            npcs[j]->kill();
                            hadBattle = true;
                            
                            std::stringstream message;
                            message << npcs[i]->getType() << " " << npcs[i]->getName() 
                                  << " убил " << npcs[j]->getType() << " " 
                                  << npcs[j]->getName();
                            
                            battle_messages.push_back(message.str());
                        }
                    }
                }
            }
        }

        for (const auto& message : battle_messages) {
            game.getBattleVisitor().notifyObservers(message);
        }
        
        co_yield GameState{hadBattle, true};
    }
    co_yield GameState{false, false};
}

Generator<GameState> CoroutineEngine::gameLoop() {
    auto movements = processMovements();
    auto battles = processBattles();

    while (running) {
        movements.next();
        battles.next();
        co_yield GameState{battles.value().hadBattle, true};
    }
    co_yield GameState{false, false};
}

void CoroutineEngine::displayMap() const {
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    
    std::cout << "\033[2J\033[H";
    std::vector<std::vector<char>> map(game_constants::MAP_SIZE, 
                                     std::vector<char>(game_constants::MAP_SIZE, ' '));

    int alive_count = 0;
    const auto& npcs = game.getNPCs();
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            int x = npc->getX();
            int y = npc->getY();
            if (x >= 0 && x < game_constants::MAP_SIZE && y >= 0 && y < game_constants::MAP_SIZE) {
                map[y][x] = npc->getType()[0];
            }
            alive_count++;
        }
    }

    std::cout << "     ";
    for (int x = 0; x < game_constants::MAP_SIZE; x += 10) {
        std::cout << std::left << std::setw(20) << x;
    }
    std::cout << "\n     ";
    for (int x = 0; x < game_constants::MAP_SIZE * 2; ++x) {
        std::cout << (x % 20 == 0 ? '|' : ' ');
    }
    std::cout << "\n\n";

    for (int y = 0; y < game_constants::MAP_SIZE; ++y) {
        std::cout << std::setw(3) << y << "  ";
        for (int x = 0; x < game_constants::MAP_SIZE; ++x) {
            std::cout << map[y][x] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "K - Рыцарь (движение: 30, убийство: 10)\n";
    std::cout << "D - Друид  (движение: 10, убийство: 10)\n";
    std::cout << "E - Эльф   (движение: 10, убийство: 50)\n";
    
    std::cout << "\nЖивых NPC: " << alive_count << "\n";
}

void CoroutineEngine::start() {
    auto game_gen = gameLoop();
    auto start_time = std::chrono::steady_clock::now();

    while (running) {
        game_gen.next();
        displayMap();

        auto current_time = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(
            current_time - start_time).count() >= 30) {
            running = false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "\nВыжившие:\n";
        const auto& npcs = game.getNPCs();
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                std::cout << npc->getType() << " " << npc->getName() 
                         << " в позиции (" << npc->getX() << "," << npc->getY() << ")\n";
            }
        }
    }
}

void CoroutineEngine::stop() {
    running = false;
} 