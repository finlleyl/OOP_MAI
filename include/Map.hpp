#pragma once
#include <vector>
#include <memory>
#include <shared_mutex>
#include "NPC.hpp"
#include "Subject.hpp"

class Map : public Subject {
    std::vector<std::unique_ptr<NPC>> npcs;
    mutable std::shared_mutex m;
public:
    void addNPC(std::unique_ptr<NPC>);
    void removeDead();
    template<typename Func>
    void forEachNPC(Func f) {
        std::shared_lock<std::shared_mutex> lock(m);
        for (auto& n : npcs) f(*n);
    }
    std::vector<NPC*> getAliveNPCs();
};