#include "rectangle.h"
#include <cmath>
#include <stdexcept>
#include "point.h"

template <Number T>
Rectangle<T>::Rectangle(const Point<T>& point1, const Point<T>& point2) {
    p1 = std::make_unique<Point<T>>(point1);
    p2 = std::make_unique<Point<T>>(point2);
}

template <Number T>
Rectangle<T>::Rectangle(const Rectangle<T>& other) {
    p1 = std::make_unique<Point<T>>(*other.p1);
    p2 = std::make_unique<Point<T>>(*other.p2);
}

template <Number T>
Rectangle<T>::Rectangle(Rectangle<T>&& other) noexcept
    : p1(std::move(other.p1)), p2(std::move(other.p2)) {}

template <Number T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& other) {
    if (this != &other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
    }
    return *this;
}

template <Number T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle<T>&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
    }
    return *this;
}

template <Number T>
std::pair<T, T> Rectangle<T>::Center() const {
    T x = (p1->getX() + p2->getX()) / static_cast<T>(2);
    T y = (p1->getY() + p2->getY()) / static_cast<T>(2);
    return std::make_pair(x, y);
}

template <Number T>
Rectangle<T>::operator double() const {
    double width = std::abs(static_cast<double>(p2->getX() - p1->getX()));
    double height = std::abs(static_cast<double>(p2->getY() - p1->getY()));
    return width * height;
}

template <Number T>
bool Rectangle<T>::operator==(const Figure<T>& other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    const auto& rect = static_cast<const Rectangle<T>&>(other);
    return *p1 == *rect.p1 && *p2 == *rect.p2;
}

template <Number T>
void Rectangle<T>::Print(std::ostream& os) const {
    os << "Rectangle coords:\n";
    os << "(x1: " << p1->getX() << ", y1: " << p1->getY() << ")\n";
    os << "(x2: " << p2->getX() << ", y2: " << p2->getY() << ")\n";
}

template <Number T>
Figure<T>* Rectangle<T>::Clone() const {
    return new Rectangle<T>(*this);
}

template <Number T>
std::istream& operator>>(std::istream& is, Rectangle<T>& r) {
    T x1, y1, x2, y2;
    is >> x1 >> y1 >> x2 >> y2;
    Point<T> p1(x1, y1);
    Point<T> p2(x2, y2);
    r = Rectangle<T>(p1, p2);
    return is;
}