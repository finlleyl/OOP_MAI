#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "figure.h"
#include "point.h"
#include "concepts.h"
#include <memory>

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

template <Number T>
Square<T>::Square(const Point<T>& point1, const Point<T>& point2) {
    p1 = std::make_unique<Point<T>>(point1);
    p2 = std::make_unique<Point<T>>(point2);
}

template <Number T>
Square<T>::Square(const Square<T>& other) {
    p1 = std::make_unique<Point<T>>(*other.p1);
    p2 = std::make_unique<Point<T>>(*other.p2);
}

template <Number T>
Square<T>::Square(Square<T>&& other) noexcept
    : p1(std::move(other.p1)), p2(std::move(other.p2)) {}

template <Number T>
Square<T>& Square<T>::operator=(const Square<T>& other) {
    if (this != &other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
    }
    return *this;
}

template <Number T>
Square<T>& Square<T>::operator=(Square<T>&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
    }
    return *this;
}

template <Number T>
std::pair<T, T> Square<T>::Center() const {
    T centerX = (p1->getX() + p2->getX()) / static_cast<T>(2);
    T centerY = (p1->getY() + p2->getY()) / static_cast<T>(2);
    return std::make_pair(centerX, centerY);
}

template <Number T>
Square<T>::operator double() const {
    double dx = static_cast<double>(p2->getX() - p1->getX());
    double dy = static_cast<double>(p2->getY() - p1->getY());
    double side = std::sqrt(dx * dx + dy * dy) / std::sqrt(2);
    return side * side;
}

template <Number T>
bool Square<T>::operator==(const Figure<T>& other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    const auto& s = static_cast<const Square<T>&>(other);
    return *p1 == *s.p1 && *p2 == *s.p2;
}

template <Number T>
void Square<T>::Print(std::ostream& os) const {
    os << "Square vertices:\n";
    os << "p1: (" << p1->getX() << ", " << p1->getY() << ")\n";
    os << "p2: (" << p2->getX() << ", " << p2->getY() << ")\n";
}

template <Number T>
Figure<T>* Square<T>::Clone() const {
    return new Square<T>(*this);
}

template <Number T>
std::istream& operator>>(std::istream& is, Square<T>& s) {
    T x, y;
    is >> x >> y;
    Point<T> p1(x, y);
    is >> x >> y;
    Point<T> p2(x, y);
    s = Square<T>(p1, p2);
    return is;
}

#endif // SQUARE_H
