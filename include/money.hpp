#ifndef MONEY_CLASS
#define MONEY_CLASS

#include <initializer_list>
#include <stddef.h>
#include <string>
#include <iostream>

using T = unsigned char;

class Money {
public:

    Money();
    Money(const std::initializer_list<T>& t);
    Money(const std::string& t);
    Money(const Money& other);
    Money(Money&& other) noexcept;

    Money& operator=(const Money& other);
    Money& operator=(Money&& other) noexcept;

    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator>(const Money& other) const;
    bool operator<=(const Money& other) const;
    bool operator>=(const Money& other) const;

    Money operator+(const Money& other);
    Money& operator+=(const Money& other);
    Money operator-(const Money& other);
    Money& operator-=(const Money& other);

    friend std::ostream& operator<<(std::ostream& os, const Money& money);

    virtual ~Money();

private:
    T* data_;
    size_t size_;

    void push_back(T value);
    void reserve(size_t cap);
    void Normalize();
    void Normalize(Money& money) const;

};

#endif // MONEY_CLASS