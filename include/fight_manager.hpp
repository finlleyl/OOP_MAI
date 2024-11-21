#ifndef FIGHT_MANAGER_HPP
#define FIGHT_MANAGER_HPP

#include "npc.hpp"
#include "concept.hpp"
#include "observer.hpp"
#include "visitor.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <fstream>

template <typename Numeric>
class FightManager : public Subject<Numeric> {
public:
    void addNPC(std::unique_ptr<NPC<Numeric>> npc);

    void startFight(Numeric maxDistance);

    void printNPCs() const;

    void loadNPCsFromFile(const std::string& filename);

    size_t getNPCCount() const;

private:
    std::vector<std::unique_ptr<NPC<Numeric>>> npcs_;
};

template <typename Numeric>
void FightManager<Numeric>::addNPC(std::unique_ptr<NPC<Numeric>> npc) {
    npcs_.push_back(std::move(npc));
}

template <typename Numeric>
void FightManager<Numeric>::startFight(Numeric maxDistance) {
    int roundNumber = 1;
    bool fightContinues = true;

    while (fightContinues) {
        this->notifyRoundStart(roundNumber);

        fightContinues = false;

        for (size_t i = 0; i < npcs_.size(); ++i) {
            if (npcs_[i]->getHealth() <= 0) continue;

            for (size_t j = i + 1; j < npcs_.size(); ++j) {
                if (npcs_[j]->getHealth() <= 0) continue;

                Numeric distance = npcs_[i]->getCoords().distance(npcs_[j]->getCoords());
                if (distance <= maxDistance) {
                    fightContinues = true;

                    CombatVisitor<Numeric> visitor(*npcs_[i], *this);
                    npcs_[j]->accept(visitor);

                    if (npcs_[j]->getHealth() <= 0) {
                        this->notifyNPCDeath(*npcs_[j], *npcs_[i]);
                    }

                    if (npcs_[i]->getHealth() <= 0) {
                        this->notifyNPCDeath(*npcs_[i], *npcs_[j]);
                        break;
                    }
                }
            }
        }

        this->notifyRoundEnd(roundNumber);
        ++roundNumber;
    }

    npcs_.erase(std::remove_if(npcs_.begin(), npcs_.end(),
        [](const std::unique_ptr<NPC<Numeric>>& npc) { return npc->getHealth() <= 0; }),
        npcs_.end());
}

template <typename Numeric>
void FightManager<Numeric>::printNPCs() const {
    for (const auto& npc : npcs_) {
        std::cout << "NPC: " << npc->getName()
                  << ", Type: " << typeid(*npc).name()
                  << ", Coords: (" << npc->getCoords().getX()
                  << ", " << npc->getCoords().getY() << ")"
                  << ", Health: " << npc->getHealth() << "\n";
    }
}

template <typename Numeric>
void FightManager<Numeric>::loadNPCsFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Bug open: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::string name, type;
        Numeric x, y;
        inputFile >> name >> type >> x >> y;

        if (type == "Elf") {
            addNPC(ElfFactory<Numeric>().createNPC(name, Coords<Numeric>(x, y), *this));
        } else if (type == "Bandit") {
            addNPC(BanditFactory<Numeric>().createNPC(name, Coords<Numeric>(x, y), *this));
        } else if (type == "Bear") {
            addNPC(BearFactory<Numeric>().createNPC(name, Coords<Numeric>(x, y), *this));
        }
    }
}

template <typename Numeric>
size_t FightManager<Numeric>::getNPCCount() const {
    return npcs_.size();
}

#endif // FIGHT_MANAGER_HPP
