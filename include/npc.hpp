#pragma once
#include <string>

class Visitor;

class NPC {
public:
    virtual ~NPC() {}
    virtual void accept(Visitor&) = 0;
    virtual int getMoveDist() const = 0;
    virtual int getKillDist() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getName() const = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual void setPos(int x, int y) = 0;
    virtual bool isAlive() const = 0;
    virtual void kill() = 0;
};

