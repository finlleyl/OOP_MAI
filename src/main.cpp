#include "Map.hpp"
#include "FactoryImpl.hpp"
#include "FightLogObserver.hpp"
#include "ConsoleLogObserver.hpp"
#include "ThreadSafeIO.hpp"
#include "FightTask.hpp"

#include <thread>
#include <chrono>
#include <random>
#include <functional>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>

int main(){
    Map map;
    FightLogObserver fileObs;
    ConsoleLogObserver consoleObs;
    map.attach(&fileObs);
    map.attach(&consoleObs);

    FactoryImpl factory;
    std::random_device rd;std::mt19937 gen(rd());
    std::uniform_int_distribution<> distType(0,2);
    std::uniform_int_distribution<> distPos(0,100);
    for(int i=0;i<50;i++){
        int t=distType(gen);
        int x=distPos(gen),y=distPos(gen);
        if(t==0) map.addNPC(factory.createElf("Elf"+std::to_string(i),x,y));
        else if(t==1) map.addNPC(factory.createRogue("Rogue"+std::to_string(i),x,y));
        else map.addNPC(factory.createBear("Bear"+std::to_string(i),x,y));
    }

    std::queue<FightTask> fightQueue;
    std::mutex fightM;
    std::condition_variable fightCV;
    std::atomic_bool running(true);

    auto moveThread = [&](){
        while(running){
            {
                auto npcs = map.getAliveNPCs();
                for (auto& n : npcs) {
                    if(!n->isAlive()) continue;
                    int nx = n->getX(), ny = n->getY();
                    int step = n->getMoveDist();
                    std::uniform_int_distribution<> d(-step, step);
                    int dx=d(gen),dy=d(gen);
                    nx+=dx;ny+=dy;
                    if(nx<0) nx=0; if(nx>100) nx=100;
                    if(ny<0) ny=0; if(ny>100) ny=100;
                    n->setPos(nx,ny);
                }
            }
            {
                auto npcs = map.getAliveNPCs();
                for(size_t i=0;i<npcs.size();i++){
                    for(size_t j=i+1;j<npcs.size();j++){
                        if(!npcs[i]->isAlive()||!npcs[j]->isAlive()) continue;
                        int dx=npcs[i]->getX()-npcs[j]->getX();
                        int dy=npcs[i]->getY()-npcs[j]->getY();
                        int dist = dx*dx+dy*dy;
                        int killDist = std::min(npcs[i]->getKillDist(), npcs[j]->getKillDist());
                        if(dist<=killDist*killDist){
                            {
                                std::lock_guard<std::mutex> lk(fightM);
                                fightQueue.push(FightTask(npcs[i],npcs[j]));
                            }
                            fightCV.notify_one();
                        }
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };

    auto fightThread = [&](){
        while(running){
            std::unique_lock<std::mutex> lk(fightM);
            fightCV.wait(lk,[&]{return !fightQueue.empty()||!running;});
            if(!running) break;
            auto task = fightQueue.front();
            fightQueue.pop();
            lk.unlock();
            task();
            map.removeDead();
        }
    };

    auto printThread = [&](){
        auto start = std::chrono::steady_clock::now();
        while(true){
            {
                char arr[101][101];
                for(int i=0;i<101;i++)for(int j=0;j<101;j++)arr[i][j]='.';
                auto npcs=map.getAliveNPCs();
                for(auto& n:npcs){
                    int x=n->getX(),y=n->getY();
                    char c='X';
                    if(n->getType()=="Elf") c='E';
                    else if(n->getType()=="Rogue") c='R';
                    else if(n->getType()=="Bear") c='B';
                    arr[y][x]=c;
                }
                ThreadSafeIO::printMap(arr);
            }
            auto now=std::chrono::steady_clock::now();
            if(std::chrono::duration_cast<std::chrono::seconds>(now - start).count()>30){
                running=false;
                fightCV.notify_all();
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        ThreadSafeIO::printMessage("Survivors:");
        auto sur = map.getAliveNPCs();
        for(auto& s:sur){
            ThreadSafeIO::printMessage(s->getType()+" "+s->getName()+" at ("+std::to_string(s->getX())+","+std::to_string(s->getY())+")");
        }
    };

    std::thread t1(moveThread);
    std::thread t2(fightThread);
    std::thread t3(printThread);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}