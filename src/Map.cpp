#include "Map.hpp"
#include <algorithm>
#include <mutex>

void Map::addNPC(std::unique_ptr<NPC> n) {
    std::unique_lock<std::shared_mutex> lock(m);
    npcs.push_back(std::move(n));
}

void Map::removeDead() {
    std::unique_lock<std::shared_mutex> lock(m);
    npcs.erase(std::remove_if(npcs.begin(), npcs.end(), [](auto& n) {return !n->isAlive();}), npcs.end());
}

std::vector<NPC*> Map::getAliveNPCs() {
    std::shared_lock<std::shared_mutex> lock(m);
    std::vector<NPC*> result;
    for (auto& n : npcs) {
        if (n->isAlive()) result.push_back(n.get());
    }
    return result;
}