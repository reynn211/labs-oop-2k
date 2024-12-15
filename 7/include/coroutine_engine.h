#pragma once
#include "gamemanager.h"
#include "game_coroutine.h"
#include "game_constants.h"
#include <chrono>
#include <atomic>
#include <mutex>

struct GameState {
    bool hadBattle;
    bool shouldContinue;
};

class CoroutineEngine {
private:
    GameManager& game;
    std::atomic<bool> running{true};
    mutable std::mutex cout_mutex;

    Generator<GameState> gameLoop();
    Generator<GameState> processMovements();
    Generator<GameState> processBattles();
    void displayMap() const;

public:
    explicit CoroutineEngine(GameManager& game);
    void start();
    void stop();
}; 