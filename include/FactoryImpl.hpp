#pragma once
#include "NPCFactory.hpp"

class FactoryImpl : public NPCFactory {
public:
    std::unique_ptr<NPC> createElf(const std::string&, int, int) override;
    std::unique_ptr<NPC> createRogue(const std::string&, int, int) override;
    std::unique_ptr<NPC> createBear(const std::string&, int, int) override;
};