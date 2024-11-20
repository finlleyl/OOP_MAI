#include "coords.hpp"

template <typename Numeric>
Coords<Numeric>::Coords(Numeric x, Numeric y) : x(x), y(y) {}

template <typename Numeric>
Coords<Numeric>::Coords() : x(0), y(0) {}

template <typename Numeric>
Numeric Coords<Numeric>::getX() const { return x; }

template <typename Numeric>
Numeric Coords<Numeric>::getY() const { return y; }

template <typename Numeric>
void Coords<Numeric>::setX(Numeric x) { this->x = x; }

template <typename Numeric>
void Coords<Numeric>::setY(Numeric y) { this->y = y; }

template <typename Numeric>
Numeric Coords<Numeric>::distance(const Coords<Numeric> &other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}