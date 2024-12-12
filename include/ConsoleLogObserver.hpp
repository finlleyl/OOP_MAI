#pragma once
#include "Observer.hpp"
#include <iostream>
#include <mutex>

class ConsoleLogObserver : public Observer {
    std::mutex m;
public:
    void update(const std::string&) override;
};