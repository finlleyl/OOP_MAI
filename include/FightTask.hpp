#pragma once
#include "NPC.hpp"

class FightTask {
    NPC* a;
    NPC* b;
public:
    FightTask(NPC*, NPC*);
    void operator()();
};