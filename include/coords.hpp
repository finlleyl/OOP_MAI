#ifndef COORDS_HPP
#define COORDS_HPP

#include "concept.hpp"
#include <cmath>

template <Numeric T>
class Coords {
public:
    Coords(T x, T y) : x(x), y(y) {}
    Coords() : x(0), y(0) {}

    T getX() const { return x; }
    T getY() const { return y; }

    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }

    T distance(const Coords<T> &other) const {
        return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }

private:
    T x;
    T y;
};

#endif // COORDS_HPP
