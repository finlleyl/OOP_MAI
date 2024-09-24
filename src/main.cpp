#include "money.hpp"
#include <iostream>
#include <string>

int main() {
    Money money1;
    std::cout << "money1 (default constructor): " << money1 << std::endl;

    Money money2 = {1, 2, 3};
    std::cout << "money2 (initializer_list): " << money2 << std::endl;

    Money money3("123456789");
    std::cout << "money3 (constructed from string): " << money3 << std::endl;

    Money money4 = money3;
    std::cout << "money4 (copy of money3): " << money4 << std::endl;

    Money money5 = std::move(money4);
    std::cout << "money5 (moved from money4): " << money5 << std::endl;
    std::cout << "money4 after move: " << money4 << std::endl;

    money1 = money2;
    std::cout << "money1 after copy assignment from money2: " << money1 << std::endl;

    money2 = std::move(money5);
    std::cout << "money2 after move assignment from money5: " << money2 << std::endl;
    std::cout << "money5 after move: " << money5 << std::endl;

    if (money1 == money2) {
        std::cout << "money1 is equal to money2" << std::endl;
    } else {
        std::cout << "money1 is not equal to money2" << std::endl;
    }

    if (money1 != money3) {
        std::cout << "money1 is not equal to money3" << std::endl;
    }

    if (money1 < money3) {
        std::cout << "money1 is less than money3" << std::endl;
    }

    if (money3 > money1) {
        std::cout << "money3 is greater than money1" << std::endl;
    }

    Money money6 = money1 + money3;
    std::cout << "money6 (money1 + money3): " << money6 << std::endl;

    money6 += money2;
    std::cout << "money6 after += money2: " << money6 << std::endl;

    Money money7 = money3 - money1;
    std::cout << "money7 (money3 - money1): " << money7 << std::endl;

    std::cout << "Trying to subtract money2 from money7 (ready for throw because money2 > money7)" << std::endl;
    try {
        money7 -= money2;
        std::cout << "money7 after -= money2: " << money7 << std::endl;
    } catch (std::invalid_argument& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "Enter a number to create a Money object: (string) ";
    std::string userInput;
    std::cin >> userInput;
    Money userMoney(userInput);
    std::cout << "You entered: " << userMoney << std::endl;

    Money result = money3 + userMoney;
    std::cout << "money3 + your number: " << result << std::endl;

    if (userMoney >= money1) {
        std::cout << "Your number is greater than or equal to money1" << std::endl;
    } else {
        std::cout << "Your number is less than money1" << std::endl;
    }

    return 0;
}
