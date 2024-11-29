#pragma once
#include "npc.h"
#include <memory>
#include <string>

class NPCFactory {
public:
    virtual ~NPCFactory() = default;
    virtual std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) = 0;
};

class KnightFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override;
};

class DruidFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override;
};

class ElfFactory : public NPCFactory {
public:
    std::shared_ptr<NPC> createNPC(const std::string& name, int x, int y) override;
}; 