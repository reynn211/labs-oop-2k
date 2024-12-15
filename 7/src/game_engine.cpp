#include "game_engine.h"
#include "game_constants.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>

GameEngine::GameEngine(GameManager& game) : game(game) {}

void GameEngine::movementThread() {
    while (running) {
        auto& npcs = game.getNPCs();
        
        for (auto& npc : npcs) {
            if (npc->isAlive()) {
                npc->move();
            }
        }
        
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!npcs[i]->isAlive() || !npcs[j]->isAlive()) continue;
                
                if (npcs[i]->distanceTo(*npcs[j]) <= npcs[i]->getKillDistance()) {
                    if (npcs[i]->attack(*npcs[j])) {
                        BattleInfo battle{
                            i, j,
                            0, 
                            0  
                        };
                        std::lock_guard<std::mutex> queue_lock(queue_mutex);
                        battle_queue.push(battle);
                    }
                }
                if (npcs[j]->distanceTo(*npcs[i]) <= npcs[j]->getKillDistance()) {
                    if (npcs[j]->attack(*npcs[i])) {
                        BattleInfo battle{
                            j, i,
                            0, 
                            0  
                        };
                        std::lock_guard<std::mutex> queue_lock(queue_mutex);
                        battle_queue.push(battle);
                    }
                }
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void GameEngine::battleThread() {
    while (running) {
        std::vector<BattleInfo> current_battles;
        
        {
            std::lock_guard<std::mutex> queue_lock(queue_mutex);
            while (!battle_queue.empty()) {
                current_battles.push_back(battle_queue.front());
                battle_queue.pop();
            }
        }
        
        if (!current_battles.empty()) {
            auto& npcs = game.getNPCs();
            
            for (const auto& battle : current_battles) {
                if (!npcs[battle.attacker]->isAlive() || !npcs[battle.target]->isAlive()) 
                    continue;
                    
                int attack_roll = npcs[battle.attacker]->rollDice();
                int defense_roll = npcs[battle.target]->rollDice();
                    
                if (attack_roll > defense_roll) {
                    npcs[battle.target]->kill();
                    
                    std::stringstream message;
                    message << npcs[battle.attacker]->getType() << " " 
                           << npcs[battle.attacker]->getName() << " убил "
                           << npcs[battle.target]->getType() << " " 
                           << npcs[battle.target]->getName()
                           << " (Атака: " << attack_roll 
                           << ", Защита: " << defense_roll << ")";
                           
                    game.getBattleVisitor().notifyObservers(message.str());
                }
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void GameEngine::start() {
    running = true;
    
    std::thread move_thread(&GameEngine::movementThread, this);
    std::thread battle_thread(&GameEngine::battleThread, this);
    
    auto start_time = std::chrono::steady_clock::now();
    while (running) {
        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            
            std::cout << "\033[2J\033[H";
            
            std::vector<std::vector<char>> map(game_constants::MAP_SIZE, 
                                             std::vector<char>(game_constants::MAP_SIZE, ' '));
            
            const auto& npcs = game.getNPCs();
            for (const auto& npc : npcs) {
                if (npc->isAlive()) {
                    int x = npc->getX();
                    int y = npc->getY();
                    if (x >= 0 && x < game_constants::MAP_SIZE && y >= 0 && y < game_constants::MAP_SIZE) {
                        map[y][x] = npc->getType()[0];
                    }
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
            
            int alive_count = 0;
            for (const auto& npc : npcs) {
                if (npc->isAlive()) alive_count++;
            }
            std::cout << "\nЖивых NPC: " << alive_count << "\n";
        }
        
        auto current_time = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(
            current_time - start_time).count() >= 30) {
            running = false;
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    stop();
    move_thread.join();
    battle_thread.join();
    
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        const auto& npcs = game.getNPCs();
        std::cout << "\nВыжившие:\n";
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                std::cout << npc->getType() << " " << npc->getName() 
                         << " в позиции (" << npc->getX() << "," << npc->getY() << ")\n";
            }
        }
    }
}

void GameEngine::stop() {
    running = false;
} 