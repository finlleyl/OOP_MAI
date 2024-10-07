#include "trapezoid.h"
#include <cmath>

Trapezoid::Trapezoid(double x1, double y1, double x2, double y2,
                     double x3, double y3, double x4, double y4)
    : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4) {
    double base1_x = std::abs(x2 - x1);
    double base2_x = std::abs(x4 - x3);

    if (base1_x != base2_x) {
        throw std::invalid_argument("No trapezoid");
    }
}

Trapezoid::Trapezoid(const Trapezoid &other) = default;

Trapezoid::Trapezoid(Trapezoid &&other) noexcept = default;

Trapezoid &Trapezoid::operator=(const Trapezoid &other) = default;

Trapezoid &Trapezoid::operator=(Trapezoid &&other) noexcept = default;

Trapezoid::~Trapezoid() = default;

std::pair<double, double> Trapezoid::Center() const {
    double center_x = (x1 + x2 + x3 + x4) / 4.0;
    double center_y = (y1 + y2 + y3 + y4) / 4.0;
    return std::make_pair(center_x, center_y);
}

Trapezoid::operator double() const {
    double area = 0.5 * std::abs(
                      x1 * y2 + x2 * y3 + x3 * y4 + x4 * y1 -
                      y1 * x2 - y2 * x3 - y3 * x4 - y4 * x1
                  );
    return area;
}

bool Trapezoid::operator==(const Figure &other) const {
    if (const auto *t = dynamic_cast<const Trapezoid *>(&other)) {
        return (x1 == t->x1 && y1 == t->y1 &&
                x2 == t->x2 && y2 == t->y2 &&
                x3 == t->x3 && y3 == t->y3 &&
                x4 == t->x4 && y4 == t->y4);
    }
    return false;
}

void Trapezoid::Print(std::ostream &os) const {
    os << "Trapezoid coords:\n";
    os << "(x1: " << x1 << ", y1: " << y1 << ")\n";
    os << "(x2: " << x2 << ", y2: " << y2 << ")\n";
    os << "(x3: " << x3 << ", y3: " << y3 << ")\n";
    os << "(x4: " << x4 << ", y4: " << y4 << ")\n";
}

Figure *Trapezoid::Clone() const {
    return new Trapezoid(*this);
}

std::istream &operator>>(std::istream &is, Trapezoid &t) {
    double x1, y1, x2, y2, x3, y3, x4, y4;
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    t = Trapezoid(x1, y1, x2, y2, x3, y3, x4, y4);
    return is;
}
