#pragma once
#include "Observer.hpp"
#include <fstream>
#include <mutex>

class FightLogObserver : public Observer {
    std::ofstream file;
    std::mutex m;
public:
    FightLogObserver();
    void update(const std::string&) override;
};