#include <gtest/gtest.h>

#include "Map.hpp"
#include "FactoryImpl.hpp"
#include "FightLogObserver.hpp"
#include "ConsoleLogObserver.hpp"
#include "ThreadSafeIO.hpp"
#include "FightTask.hpp"
#include "Elf.hpp"
#include "Rogue.hpp"
#include "NPC.hpp"

TEST(FactoryTest, CreateNPCs) {
    FactoryImpl factory;
    
    auto elf = factory.createElf("Legolas", 10, 20);

    EXPECT_EQ(elf->getType(), "Elf");
}

TEST(NPCTest, InitialState) {
    Elf elf("Elfy", 10, 10);

    EXPECT_EQ(elf.getType(), "Elf");
}

TEST(NPCTest, KillNPC) {
    Elf elf("DeadElf", 20, 20);

    elf.kill();

    EXPECT_FALSE(elf.isAlive());
}

TEST(MapTest, AddAndGetNPCs) {
    Map map;
    FactoryImpl factory;

    map.addNPC(factory.createElf("E1", 10, 10));
    map.addNPC(factory.createRogue("R1", 5, 5));
    auto alive = map.getAliveNPCs();

    EXPECT_EQ(alive.size(), 2u);
}

TEST(MapTest, RemoveDeadNPCs) {
    Map map;
    FactoryImpl factory;
    map.addNPC(factory.createElf("E2", 10, 10));
    map.addNPC(factory.createRogue("R2", 5, 5));

    auto npcs = map.getAliveNPCs();
    npcs[0]->kill();
    map.removeDead();
    auto aliveAfter = map.getAliveNPCs();

    EXPECT_EQ(aliveAfter.size(), 1u);
}

TEST(FightTest, OneOrBothDie) {
    Elf elf("FighterElf",50,50);
    Rogue rogue("FighterRogue",51,50);
    FightTask fight(&elf, &rogue);

    fight();

    EXPECT_FALSE(elf.isAlive() && rogue.isAlive());
}