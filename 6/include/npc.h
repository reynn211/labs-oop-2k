#pragma once
#include <string>
#include <memory>

class NPC {
protected:
    std::string name;
    int x, y;
    std::string type;

public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual bool attack(NPC& other) = 0;
    
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
};

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y);
    bool attack(NPC& other) override;
};

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y);
    bool attack(NPC& other) override;
}; 