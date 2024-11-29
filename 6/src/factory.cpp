#include "factory.h"

std::shared_ptr<NPC> KnightFactory::createNPC(const std::string& name, int x, int y) {
    return std::make_shared<Knight>(name, x, y);
}

std::shared_ptr<NPC> DruidFactory::createNPC(const std::string& name, int x, int y) {
    return std::make_shared<Druid>(name, x, y);
}

std::shared_ptr<NPC> ElfFactory::createNPC(const std::string& name, int x, int y) {
    return std::make_shared<Elf>(name, x, y);
} 