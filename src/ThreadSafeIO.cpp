#include "ThreadSafeIO.hpp"

std::mutex ThreadSafeIO::m;

void ThreadSafeIO::printMap(char arr[101][101]) {
    std::lock_guard<std::mutex> lock(m);
    for(int i = 0; i < 101; i++) {
        for(int j = 0; j < 101; j++) std::cout << arr[i][j];
        std::cout << "\n";
    }
}

void ThreadSafeIO::printMessage(const std::string& s) {
    std::lock_guard<std::mutex> lock(m);
    std::cout << s << "\n";
}