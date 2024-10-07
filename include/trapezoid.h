#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <iostream>
#include "figure.h"

class Trapezoid : public Figure {
public:
    Trapezoid(double x1, double y1, double x2, double y2,
              double x3, double y3, double x4, double y4);

    Trapezoid(const Trapezoid &other);

    Trapezoid(Trapezoid &&other) noexcept;

    ~Trapezoid() override;

    Trapezoid &operator=(const Trapezoid &other);

    Trapezoid &operator=(Trapezoid &&other) noexcept;

    std::pair<double, double> Center() const override;

    explicit operator double() const override;

    bool operator==(const Figure &other) const override;

    void Print(std::ostream &os) const override;

    friend std::istream &operator>>(std::istream &is, Trapezoid &t);

    Figure *Clone() const override;

private:
    double x1, y1;
    double x2, y2;
    double x3, y3;
    double x4, y4;
};

#endif // TRAPEZOID_H
