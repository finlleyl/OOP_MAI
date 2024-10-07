#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include "figure.h"

class Square : public Figure {
public:
    Square(double x1, double y1, double x2, double y2);

    Square(const Square &other);

    Square(Square &&other) noexcept;

    ~Square() override;

    Square &operator=(const Square &other);

    Square &operator=(Square &&other) noexcept;

    std::pair<double, double> Center() const override;

    explicit operator double() const override;

    bool operator==(const Figure &other) const override;

    void Print(std::ostream &os) const override;

    friend std::istream &operator>>(std::istream &is, Square &s);

    Figure *Clone() const override;

private:
    double x1, y1;
    double x2, y2;
};

#endif // SQUARE_H
