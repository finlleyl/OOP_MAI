#include "FightLogObserver.hpp"

FightLogObserver::FightLogObserver() : file("log.txt", std::ios::app) {}

void FightLogObserver::update(const std::string& s) {
    std::lock_guard<std::mutex> lock(m);
    file << s << "\n";
}