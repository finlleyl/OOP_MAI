#include "square.h"
#include <cmath>
#include <stdexcept>

Square::Square(double x1, double y1, double x2, double y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    if (std::abs(dx) != std::abs(dy)) {
        throw std::invalid_argument("Not a square");
    }
}

Square::Square(const Square &other) = default;

Square::Square(Square &&other) noexcept = default;

Square &Square::operator=(const Square &other) = default;

Square &Square::operator=(Square &&other) noexcept = default;

Square::~Square() = default;

std::pair<double, double> Square::Center() const {
    double center_x = (x1 + x2) / 2.0;
    double center_y = (y1 + y2) / 2.0;
    return std::make_pair(center_x, center_y);
}

Square::operator double() const {
    double side = std::abs(x2 - x1);
    return side * side;
}

bool Square::operator==(const Figure &other) const {
    if (const auto *s = dynamic_cast<const Square *>(&other)) {
        return (x1 == s->x1 && y1 == s->y1 &&
                x2 == s->x2 && y2 == s->y2);
    }
    return false;
}

void Square::Print(std::ostream &os) const {
    os << "Square coords:\n";
    os << "(x1: " << x1 << ", y1: " << y1 << ")\n";
    os << "(x2: " << x2 << ", y2: " << y2 << ")\n";
}

Figure *Square::Clone() const {
    return new Square(*this);
}

std::istream &operator>>(std::istream &is, Square &s) {
    double x1, y1, x2, y2;
    is >> x1 >> y1 >> x2 >> y2;
    s = Square(x1, y1, x2, y2);
    return is;
}
