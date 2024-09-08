#include "function.h"
#include <string>
#include <iomanip>
#include <sstream>

std::string convertTo24H(int hour, int minute, const std::string &period) {
    if (period == "AM" && hour == 12) {
        hour = 0;
    } else if (period == "PM" && hour != 12) {
        hour += 12;
    }

    std::ostringstream result;

    result << std::setw(2) << std::setfill('0') << hour;
    result << std::setw(2) << std::setfill('0') << minute;

    return result.str();
}
