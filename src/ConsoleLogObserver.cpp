#include "ConsoleLogObserver.hpp"

void ConsoleLogObserver::update(const std::string& s) {
    std::lock_guard<std::mutex> lock(m);
    std::cout << s << "\n";
}