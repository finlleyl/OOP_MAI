#ifndef FIGURE_H
#define FIGURE_H

#include <utility>
#include <stdexcept>


class Figure {
public:
    virtual ~Figure() noexcept = default;

    virtual std::pair<double, double> Center() const = 0;

    virtual explicit operator double() const = 0;

    virtual Figure *Clone() const = 0;

    virtual bool operator==(const Figure &other) const = 0;

    virtual void Print(std::ostream &os) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);
};

#endif //FIGURE_H
