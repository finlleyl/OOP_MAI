#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "figure.h"
#include "point.h"
#include <memory>

template <Number T>
class Rectangle : public Figure<T> {
public:
    Rectangle(const Point<T>& point1, const Point<T>& point2);
    Rectangle(const Rectangle<T>& other);
    Rectangle(Rectangle<T>&& other) noexcept;

    ~Rectangle() override = default;

    Rectangle<T>& operator=(const Rectangle<T>& other);
    Rectangle<T>& operator=(Rectangle<T>&& other) noexcept;

    std::pair<T, T> Center() const override;
    explicit operator double() const override;
    bool operator==(const Figure<T>& other) const override;
    void Print(std::ostream& os) const override;
    Figure<T>* Clone() const override;

    template <Number U>
    friend std::istream& operator>>(std::istream& is, Rectangle<U>& r);

private:
    std::unique_ptr<Point<T>> p1;
    std::unique_ptr<Point<T>> p2;
};

#endif // RECTANGLE_H


