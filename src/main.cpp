#include <iostream>
#include <string>
#include <function.h>

int main() {
    int hour, minute;
    std::string period;

    std::cout << "Enter hours (1-12): ";
    std::cin >> hour;
    std::cout << "Enter minutes (0-59): ";
    std::cin >> minute;
    std::cout << "Enter period (AM/PM): ";
    std::cin >> period;

    std::string result = convertTo24H(hour, minute, period);

    std::cout << "24H format: " << result << std::endl;

    return 0;
}