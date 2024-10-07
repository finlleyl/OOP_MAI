#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "figure.h"

class Rectangle : public Figure {
public:
    Rectangle(double, double, double, double);

    Rectangle(const Rectangle &other);

    Rectangle(Rectangle &&other) noexcept;

    ~Rectangle() override;

    Rectangle &operator=(const Rectangle &other);

    Rectangle &operator=(Rectangle &&other) noexcept;

    std::pair<double, double> Center() const override;

    explicit operator double() const override;

    bool operator==(const Figure &other) const override;

    void Print(std::ostream &os) const override;

    friend std::istream &operator>>(std::istream &is, Rectangle &r);

    Figure *Clone() const override;

private:
    double x1, y1;
    double x2, y2;
};

#endif //RECTANGLE_H
