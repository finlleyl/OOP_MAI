#include "FactoryImpl.hpp"
#include "Elf.hpp"
#include "Rogue.hpp"
#include "Bear.hpp"

std::unique_ptr<NPC> FactoryImpl::createElf(const std::string& name, int x, int y) {
    return std::make_unique<Elf>(name, x, y);
}

std::unique_ptr<NPC> FactoryImpl::createRogue(const std::string& name, int x, int y) {
    return std::make_unique<Rogue>(name, x, y);
}

std::unique_ptr<NPC> FactoryImpl::createBear(const std::string& name, int x, int y) {
    return std::make_unique<Bear>(name, x, y);
}