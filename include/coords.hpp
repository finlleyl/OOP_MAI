#ifndef COORDS_HPP
#define COORDS_HPP

#include "concept.hpp"

template <typename Numeric>
class Coords {
public:
    Coords(Numeric x, Numeric y);
    Coords();

    Numeric getX() const;
    Numeric getY() const;

    void setX(Numeric x);
    void setY(Numeric y);

    Numeric distance(const Coords<Numeric> &other) const;

private:
    Numeric x;
    Numeric y;
};

#endif // COORDS_HPP