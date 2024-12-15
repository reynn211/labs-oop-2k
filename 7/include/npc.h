#pragma once
#include "game_constants.h"
#include <string>
#include <memory>
#include <random>
#include <atomic>

class NPC {
protected:
    std::string name;
    int x, y;
    std::string type;
    std::atomic<bool> alive;

public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual bool attack(NPC& other) = 0;
    virtual int getMoveDistance() const = 0;
    virtual int getKillDistance() const = 0;
    
    void move();
    int rollDice();
    bool isAlive() const { return alive; }
    void kill() { alive = false; }
    
    std::string getName() const { return name; }
    std::string getType() const { return type; }
    int getX() const { return x; }
    int getY() const { return y; }
    
    double distanceTo(const NPC& other) const;
};

class Knight : public NPC {
public:
    Knight(const std::string& name, int x, int y);
    bool attack(NPC& other) override;
    int getMoveDistance() const override { return 30; }
    int getKillDistance() const override { return 10; }
};

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y);
    bool attack(NPC& other) override;
    int getMoveDistance() const override { return 10; }
    int getKillDistance() const override { return 10; }
};

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y);
    bool attack(NPC& other) override;
    int getMoveDistance() const override { return 10; }
    int getKillDistance() const override { return 50; }
};