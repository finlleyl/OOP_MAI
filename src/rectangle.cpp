#include "rectangle.h"
#include <cmath>
#include <stdexcept>


Rectangle::Rectangle(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

Rectangle::Rectangle(const Rectangle &other) = default;

Rectangle::Rectangle(Rectangle &&other) noexcept = default;

Rectangle &Rectangle::operator=(const Rectangle &other) = default;

Rectangle &Rectangle::operator=(Rectangle &&other) noexcept = default;

std::pair<double, double> Rectangle::Center() const {
    double center_x = (x1 + x2) / 2;
    double center_y = (y1 + y2) / 2;

    return std::make_pair(center_x, center_y);
}

Rectangle::operator double() const {
    double width = std::abs(x2 - x1);
    double height = std::abs(y2 - y1);

    return width * height;
}


bool Rectangle::operator==(const Figure &other) const {
    if (const auto *rect = dynamic_cast<const Rectangle *>(&other)) {
        return (x1 == rect->x1 && y1 == rect->y1 &&
                x2 == rect->x2 && y2 == rect->y2);
    }
    return false;
}

void Rectangle::Print(std::ostream &os) const {
    os << "Rectangle coords:\n";
    os << "(x1: " << x1 << ", y1: " << y1 << ")\n";
    os << "(x2: " << x2 << ", y2: " << y2 << ")\n";
}

Figure *Rectangle::Clone() const {
    return new Rectangle(*this);
}

Rectangle::~Rectangle() = default;

std::istream &operator>>(std::istream &is, Rectangle &r) {
    double x1, y1, x2, y2;
    is >> x1 >> y1 >> x2 >> y2;
    r = Rectangle(x1, y1, x2, y2);

    return is;
}
