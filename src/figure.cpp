#include "figure.h"


std::ostream &operator<<(std::ostream &os, const Figure &figure) {
    figure.Print(os);
    return os;
}