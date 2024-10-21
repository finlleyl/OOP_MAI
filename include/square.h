#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "figure.h"
#include "point.h"

template <typename T>
concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <Number T>
class Square : public Figure<T> {
public:
    Square(const Point<T>& p1, const Point<T>& p2);
    Square(const Square<T>& other);
    Square(Square<T>&& other) noexcept;

    ~Square() override = default;

    Square<T>& operator=(const Square<T>& other);
    Square<T>& operator=(Square<T>&& other) noexcept;


    std::pair<T, T> Center() const override;
    explicit operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    void Print(std::ostream& os) const override;
    Figure<T>* Clone() const override;

    template <Number U>
    friend std::istream& operator>>(std::istream& is, Square<U>& s);

private:
    std::unique_ptr<Point<T>> p1;
    std::unique_ptr<Point<T>> p2;
};



#endif // SQUARE_H
