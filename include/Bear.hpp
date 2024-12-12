#pragma once
#include "NPC.hpp"
#include <atomic>

class Bear : public NPC {
    std::string name;
    int x, y;
    std::atomic_bool alive;
public:
    Bear(const std::string&, int, int);
    void accept(Visitor&) override;
    int getMoveDist() const override;
    int getKillDist() const override;
    std::string getType() const override;
    std::string getName() const override;
    int getX() const override;
    int getY() const override;
    void setPos(int, int) override;
    bool isAlive() const override;
    void kill() override;
};