#pragma once
#include <memory>
#include <string>
#include "NPC.hpp"

class NPCFactory {
public:
    virtual ~NPCFactory() {}
    virtual std::unique_ptr<NPC> createElf(const std::string&, int, int) = 0;
    virtual std::unique_ptr<NPC> createRogue(const std::string&, int, int) = 0;
    virtual std::unique_ptr<NPC> createBear(const std::string&, int, int) = 0;
};