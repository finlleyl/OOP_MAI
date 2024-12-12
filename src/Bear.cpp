#include "Bear.hpp"
#include "Visitor.hpp"

Bear::Bear(const std::string& n, int X, int Y)
    : name(n), x(X), y(Y), alive(true) {}

void Bear::accept(Visitor& v) { v.visit(*this); }
int Bear::getMoveDist() const { return 5; }
int Bear::getKillDist() const { return 10; }
std::string Bear::getType() const { return "Bear"; }
std::string Bear::getName() const { return name; }
int Bear::getX() const { return x; }
int Bear::getY() const { return y; }
void Bear::setPos(int X, int Y) { x = X; y = Y; }
bool Bear::isAlive() const { return alive; }
void Bear::kill() { alive = false; }