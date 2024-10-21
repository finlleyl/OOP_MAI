#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "figure.h"
#include "point.h"

template <Number T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid(const Point<T>& p1, const Point<T>& p2,
              const Point<T>& p3, const Point<T>& p4);
    Trapezoid(const Trapezoid<T>& other);
    Trapezoid(Trapezoid<T>&& other) noexcept;

    ~Trapezoid() override = default;

    Trapezoid<T>& operator=(const Trapezoid<T>& other);
    Trapezoid<T>& operator=(Trapezoid<T>&& other) noexcept;

    std::pair<T, T> Center() const override;
    explicit operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    void Print(std::ostream& os) const override;
    Figure<T>* Clone() const override;

    template <Number U>
    friend std::istream& operator>>(std::istream& is, Trapezoid<U>& t);

private:
    std::unique_ptr<Point<T>> p1;
    std::unique_ptr<Point<T>> p2;
    std::unique_ptr<Point<T>> p3;
    std::unique_ptr<Point<T>> p4;
};

#endif // TRAPEZOID_H
