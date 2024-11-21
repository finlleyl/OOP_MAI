// tests.cpp
#include <gtest/gtest.h>
#include "coords.hpp"
#include "npc.hpp"
#include "observer.hpp"
#include "visitor.hpp"
#include "fight_manager.hpp"
#include <memory>

TEST(CoordsTest, DistanceCalculation) {
    Coords<double> pointA(0.0, 0.0);
    Coords<double> pointB(3.0, 4.0);

    double distance = pointA.distance(pointB);

    EXPECT_DOUBLE_EQ(distance, 5.0);
}

TEST(NPCTest, Creation) {
    BearFactory<double> bearFactory;
    FightManager<double> manager;

    auto bear = bearFactory.createNPC("Bear", Coords<double>(0.0, 0.0), manager);

    EXPECT_EQ(bear->getName(), "Bear");
}

TEST(CombatTest, BearAttacksElf) {
    FightManager<double> manager;
    BearFactory<double> bearFactory;
    ElfFactory<double> elfFactory;

    auto bear = bearFactory.createNPC("Bear", Coords<double>(0.0, 0.0), manager);
    auto elf = elfFactory.createNPC("Elf", Coords<double>(1.0, 1.0), manager);

    CombatVisitor<double> visitor(*bear, manager);
    elf->accept(visitor);

    EXPECT_EQ(elf->getHealth(), 0);
}

template <typename Numeric>
class TestObserver : public Observer<Numeric> {
public:
    std::vector<std::string> notifications;

    void onNPCDeath(const NPC<Numeric>& npc, const NPC<Numeric>& killer) override {
        notifications.push_back("onNPCDeath: " + npc.getName() + " killed by " + killer.getName());
    }

    void onRoundStart(int roundNumber) override {
        notifications.push_back("onRoundStart: " + std::to_string(roundNumber));
    }

    void onRoundEnd(int roundNumber) override {
        notifications.push_back("onRoundEnd: " + std::to_string(roundNumber));
    }

    void onAttack(const NPC<Numeric>& attacker, const NPC<Numeric>& target) override {
        notifications.push_back("onAttack: " + attacker.getName() + " attacked " + target.getName());
    }

    void onCreate(const NPC<Numeric>& npc) override {
        notifications.push_back("onCreate: " + npc.getName());
    }
};

TEST(ObserverTest, Notifications) {
    FightManager<double> manager;
    TestObserver<double> observer;
    manager.addObserver(&observer);

    BearFactory<double> bearFactory;
    ElfFactory<double> elfFactory;

    auto bear = bearFactory.createNPC("Bear", Coords<double>(0.0, 0.0), manager);
    auto elf = elfFactory.createNPC("Elf", Coords<double>(1.0, 1.0), manager);

    manager.addNPC(std::move(bear));
    manager.addNPC(std::move(elf));

    manager.startFight(10.0);

    ASSERT_GE(observer.notifications.size(), 5);
}

TEST(FightManagerTest, RemoveDeadNPCs) {
    FightManager<double> manager;
    BearFactory<double> bearFactory;
    ElfFactory<double> elfFactory;

    auto bear = bearFactory.createNPC("Bear", Coords<double>(0.0, 0.0), manager);
    auto elf = elfFactory.createNPC("Elf", Coords<double>(1.0, 1.0), manager);

    manager.addNPC(std::move(bear));
    manager.addNPC(std::move(elf));

    manager.startFight(10.0);

    EXPECT_EQ(manager.getNPCCount(), 1);
}