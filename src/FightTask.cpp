#include "FightTask.hpp"
#include <random>

FightTask::FightTask(NPC* A, NPC* B) : a(A), b(B) {}

void FightTask::operator()() {
    if (!a->isAlive() || !b->isAlive()) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6);

    int attack = dist(gen);
    int defense = dist(gen);

    if (attack > defense) b->kill();
    if (defense > attack) a->kill();
}