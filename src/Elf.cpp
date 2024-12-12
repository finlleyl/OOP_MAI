#include "Elf.hpp"
#include "Visitor.hpp"

Elf::Elf(const std::string& n, int X, int Y)
    : name(n), x(X), y(Y), alive(true) {}

void Elf::accept(Visitor& v) { v.visit(*this); }
int Elf::getMoveDist() const { return 10; }
int Elf::getKillDist() const { return 50; }
std::string Elf::getType() const { return "Elf"; }
std::string Elf::getName() const { return name; }
int Elf::getX() const { return x; }
int Elf::getY() const { return y; }
void Elf::setPos(int X, int Y) { x = X; y = Y; }
bool Elf::isAlive() const { return alive; }
void Elf::kill() { alive = false; }