#pragma once
#include "gamemanager.h"
#include "game_constants.h"
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>

class GameEngine {
private:
    struct BattleInfo {
        size_t attacker;
        size_t target;
        int attack_roll;
        int defense_roll;
    };
    
    std::queue<BattleInfo> battle_queue;
    std::mutex queue_mutex;
    std::mutex cout_mutex;
    GameManager& game;
    std::atomic<bool> running{true};
    
    void movementThread();
    void battleThread();
    
public:
    explicit GameEngine(GameManager& game);
    void start();
    void stop();
}; 