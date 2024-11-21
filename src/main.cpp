#include "fight_manager.hpp"
#include "npc.hpp"
#include "observer.hpp"
#include <memory>
#include <iostream>

int main() {
    FightManager<double> manager;

    ConsoleObserver<double> consoleObserver;
    FileObserver<double> fileObserver("battle_log.txt", "npcs_list.txt");

    manager.addObserver(&consoleObserver);
    manager.addObserver(&fileObserver);

    BearFactory<double> bearFactory;
    ElfFactory<double> elfFactory;
    BanditFactory<double> banditFactory;

    std::string npcFilename = "npcs.txt";
    manager.loadNPCsFromFile(npcFilename);


    std::cout << "NPC list before fight:\n";
    manager.printNPCs();

    manager.startFight(500.0);

    std::cout << "\nNPC list after fight:\n";
    manager.printNPCs();

    return 0;
}
