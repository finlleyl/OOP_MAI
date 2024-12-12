#include "Rogue.hpp"
#include "Visitor.hpp"

Rogue::Rogue(const std::string& n, int X, int Y)
    : name(n), x(X), y(Y), alive(true) {}

void Rogue::accept(Visitor& v) { v.visit(*this); }
int Rogue::getMoveDist() const { return 10; }
int Rogue::getKillDist() const { return 10; }
std::string Rogue::getType() const { return "Rogue"; }
std::string Rogue::getName() const { return name; }
int Rogue::getX() const { return x; }
int Rogue::getY() const { return y; }
void Rogue::setPos(int X, int Y) { x = X; y = Y; }
bool Rogue::isAlive() const { return alive; }
void Rogue::kill() { alive = false; }