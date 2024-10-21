#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "figure.h"
#include "point.h"
#include "concepts.h"
#include <memory>

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

template <Number T>
Trapezoid<T>::Trapezoid(const Point<T>& point1, const Point<T>& point2,
                        const Point<T>& point3, const Point<T>& point4) {
    p1 = std::make_unique<Point<T>>(point1);
    p2 = std::make_unique<Point<T>>(point2);
    p3 = std::make_unique<Point<T>>(point3);
    p4 = std::make_unique<Point<T>>(point4);
}

template <Number T>
Trapezoid<T>::Trapezoid(const Trapezoid<T>& other) {
    p1 = std::make_unique<Point<T>>(*other.p1);
    p2 = std::make_unique<Point<T>>(*other.p2);
    p3 = std::make_unique<Point<T>>(*other.p3);
    p4 = std::make_unique<Point<T>>(*other.p4);
}

template <Number T>
Trapezoid<T>::Trapezoid(Trapezoid<T>&& other) noexcept
    : p1(std::move(other.p1)), p2(std::move(other.p2)),
      p3(std::move(other.p3)), p4(std::move(other.p4)) {}

template <Number T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid<T>& other) {
    if (this != &other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
    }
    return *this;
}

template <Number T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid<T>&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
    }
    return *this;
}

template <Number T>
std::pair<T, T> Trapezoid<T>::Center() const {
    T centerX = (p1->getX() + p2->getX() + p3->getX() + p4->getX()) / static_cast<T>(4);
    T centerY = (p1->getY() + p2->getY() + p3->getY() + p4->getY()) / static_cast<T>(4);
    return std::make_pair(centerX, centerY);
}

template <Number T>
Trapezoid<T>::operator double() const {
    double area = 0.5 * std::abs(
        static_cast<double>(p1->getX() * p2->getY() + p2->getX() * p3->getY() +
                            p3->getX() * p4->getY() + p4->getX() * p1->getY()) -
        static_cast<double>(p1->getY() * p2->getX() + p2->getY() * p3->getX() +
                            p3->getY() * p4->getX() + p4->getY() * p1->getX())
    );
    return area;
}

template <Number T>
bool Trapezoid<T>::operator==(const Figure<T>& other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    const auto& t = static_cast<const Trapezoid<T>&>(other);
    return *p1 == *t.p1 && *p2 == *t.p2 && *p3 == *t.p3 && *p4 == *t.p4;
}

template <Number T>
void Trapezoid<T>::Print(std::ostream& os) const {
    os << "Trapezoid vertices:\n";
    os << "p1: (" << p1->getX() << ", " << p1->getY() << ")\n";
    os << "p2: (" << p2->getX() << ", " << p2->getY() << ")\n";
    os << "p3: (" << p3->getX() << ", " << p3->getY() << ")\n";
    os << "p4: (" << p4->getX() << ", " << p4->getY() << ")\n";
}

template <Number T>
Figure<T>* Trapezoid<T>::Clone() const {
    return new Trapezoid<T>(*this);
}

template <Number T>
std::istream& operator>>(std::istream& is, Trapezoid<T>& t) {
    T x, y;
    is >> x >> y;
    auto p1 = std::make_unique<Point<T>>(x, y);
    is >> x >> y;
    auto p2 = std::make_unique<Point<T>>(x, y);
    is >> x >> y;
    auto p3 = std::make_unique<Point<T>>(x, y);
    is >> x >> y;
    auto p4 = std::make_unique<Point<T>>(x, y);
    t = Trapezoid<T>(*p1, *p2, *p3, *p4);
    return is;
}

#endif // TRAPEZOID_H
