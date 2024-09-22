#include "money.hpp"


int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    Money m1(s1);
    Money m2(s2);

    Money sum = m1 + m2;
    Money diff = m1 - m2;

    std::cout << "m1: ";
    std::cout << m1 << std::endl;

    std::cout << "m2: ";
    std::cout << m2 << std::endl;

    std::cout << "Сумма: ";
    std::cout << sum << std::endl;

    std::cout << "Разница: ";
    std::cout << diff << std::endl;

    if (m1 > m2) {
        std::cout << "m1 больше m2" << std::endl;
    } else {
        std::cout << "m1 не больше m2" << std::endl;
    }

    return 0;
}