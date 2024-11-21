#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "npc.hpp"
#include "concept.hpp"

template <typename Numeric>
class Observer {
public:
    virtual void onNPCDeath(const NPC<Numeric>& npc, const NPC<Numeric>& killer) = 0;
    virtual void onRoundStart(int roundNumber) = 0;
    virtual void onRoundEnd(int roundNumber) = 0;
    virtual void onAttack(const NPC<Numeric>& attacker, const NPC<Numeric>& target) = 0;
    virtual void onCreate(const NPC<Numeric>& npc) = 0;
    virtual ~Observer() = default;
};

template <typename Numeric>
class Subject {
public:
    void addObserver(Observer<Numeric>* observer) {
        observers_.push_back(observer);
    }

    void removeObserver(Observer<Numeric>* observer) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    void notifyNPCDeath(const NPC<Numeric>& npc, const NPC<Numeric>& killer) {
        for (auto observer : observers_) {
            observer->onNPCDeath(npc, killer);
        }
    }

    void notifyRoundStart(int roundNumber) {
        for (auto observer : observers_) {
            observer->onRoundStart(roundNumber);
        }
    }

    void notifyRoundEnd(int roundNumber) {
        for (auto observer : observers_) {
            observer->onRoundEnd(roundNumber);
        }
    }

    void notifyAttack(const NPC<Numeric>& attacker, const NPC<Numeric>& target) {
        for (auto observer : observers_) {
            observer->onAttack(attacker, target);
        }
    }

    void notifyNPCCreated(const NPC<Numeric>& npc) {
        for (auto observer : observers_) {
            observer->onCreate(npc);
        }
    }

private:
    std::vector<Observer<Numeric>*> observers_;
};

template <typename Numeric>
class ConsoleObserver : public Observer<Numeric> {
public:
    void onNPCDeath(const NPC<Numeric>& npc, const NPC<Numeric>& killer) override {
        std::cout << "NPC \"" << npc.getName() << "\" killed by \"" << killer.getName() << "\".\n";
    }

    void onRoundStart(int roundNumber) override {
        std::cout << "Round " << roundNumber << " started.\n";
    }

    void onRoundEnd(int roundNumber) override {
        std::cout << "Round " << roundNumber << " ended.\n";
    }

    void onAttack(const NPC<Numeric>& attacker, const NPC<Numeric>& target) override {
        std::cout << "NPC \"" << attacker.getName() << "\" attacked \"" << target.getName() << "\".\n";
        std::cout << "NPC \"" << target.getName() << "\" has " << target.getHealth() << " health left.\n";
    }

    void onCreate(const NPC<Numeric>& npc) override {
        return;
    }
};

template <typename Numeric>
class FileObserver : public Observer<Numeric> {
public:
    FileObserver(const std::string& filename, const std::string& filenpc) : logFile(filename, std::ios::app), npc_file(filenpc, std::ios::app) {}

    void onNPCDeath(const NPC<Numeric>& npc, const NPC<Numeric>& killer) override {
        logFile << "NPC \"" << npc.getName() << "\" killed by \"" << killer.getName() << "\".\n";
    }

    void onRoundStart(int roundNumber) override {
        logFile << "Round " << roundNumber << " started.\n";
    }

    void onRoundEnd(int roundNumber) override {
        logFile << "Round " << roundNumber << " ended.\n";
    }

    void onAttack(const NPC<Numeric>& attacker, const NPC<Numeric>& target) override {
        logFile << "NPC \"" << attacker.getName() << "\" attacked \"" << target.getName() << "\".\n";
        logFile << "NPC \"" << target.getName() << "\" has " << target.getHealth() << " health left.\n";
    }

    void onCreate(const NPC<Numeric>& npc) override {
        logFile << "NPC: " << npc.getName()
                << ", Type: " << typeid(npc).name()
                << ", Coords: (" << npc.getCoords().getX()
                << ", " << npc.getCoords().getY() << ")"
                << ", Health: " << npc.getHealth()
                << ", Damage: " << npc.getDamage() << "\n";
    }

private:
    std::ofstream logFile;
    std::ofstream npc_file;
};


#endif // OBSERVER_HPP
