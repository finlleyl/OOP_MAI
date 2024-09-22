#include "money.hpp"
#include <algorithm>
#include <stdexcept>

Money::Money() : data_(nullptr), size_(0) {}

Money::Money(const std::initializer_list<T>& t) : size_(t.size()) {
    data_ = new T[size_];

    std::copy(t.begin(), t.end(), data_);

    Normalize();
}

Money::Money(const std::string& t) {
    std::string clean_string;

    for (T c : t) {
        if (c != '.') {
            clean_string += c;
        }
    }

    size_ = clean_string.length();
    data_ = new T[size_];

    for (size_t i = 0; i < size_; ++i) {
        data_[i] = clean_string[size_ - i - 1] - '0';
    }

    Normalize();
}

Money::Money(const Money& other) : size_(other.size_) {
    data_ = new T[size_];
    std::copy(other.data_, other.data_ + size_, data_);

}

Money::Money(Money&& other) noexcept : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
}

Money& Money::operator=(const Money& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        data_ = new T[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    }

    return *this;
}

Money& Money::operator=(Money&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }

    return *this;
}

bool Money::operator==(const Money& other) const {
    if (size_ != other.size_) {
        return false;
    }

    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }

    return true;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator<(const Money& other) const {
    if (size_ < other.size_) {
        return true;
    } else if (size_ > other.size_) {
        return false;
    }

    for (size_t i = 0; i < size_; ++i) {
        if (data_[size_ - i - 1] < other.data_[size_ - i - 1]) {
            return true;
        } else if (data_[size_ - i - 1] > other.data_[size_ - i - 1]) {
            return false;
        }
    }

    return false;
} 

bool Money::operator>(const Money& other) const {
    return !(*this < other) && *this != other;
}

bool Money::operator<=(const Money& other) const {
    return *this < other || *this == other;
}

bool Money::operator>=(const Money& other) const {
    return *this > other || *this == other;
}

void Money::push_back(T value) {
    T* new_data = new T[size_ + 1];
    std::copy(data_, data_ + size_, new_data);
    new_data[size_] = value;

    delete[] data_;
    data_ = new_data;
    ++size_;
}


Money Money::operator+(const Money& other){
    Money result;
    size_t max_size = std::max(size_, other.size_) + 1;
    result.reserve(max_size);

    T carry = 0;
    for (size_t i = 0; i < max_size; ++i) {
        T sum = carry;
        if (i < size_) {
            sum += data_[i];
        }
        if (i < other.size_) {
            sum += other.data_[i];
        }

        result.push_back(sum % 10);
        carry = sum / 10;
    }

    if (carry) {
        result.push_back(carry);
    }

    Normalize(result);

    return result;
}

Money& Money::operator+=(const Money& other) {
    *this = *this + other;
    return *this;
}   

Money Money::operator-(const Money& other) {
    if (*this < other) {
        throw std::invalid_argument("Subtraction result is negative");
    }

    Money result;
    size_t max_size = std::max(size_, other.size_);
    result.reserve(max_size);

    int carry = 0;
    for (size_t i = 0; i < max_size; ++i) {
        int diff = (i < size_ ? static_cast<int>(data_[i]) : 0) - carry;

        if (i < other.size_) {
            diff -= static_cast<int>(other.data_[i]);
        }

        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result.push_back(static_cast<unsigned char>(diff));
    }

    result.Normalize();

    return result;
}

Money& Money::operator-=(const Money& other) {
    *this = *this - other;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    if (money.size_ <= 2) {
        os << "0.";
        for (size_t i = money.size_; i > 0; --i) {
            T digit = money.data_[i - 1];
            os << static_cast<int>(digit);
        }
    } else {
        for (size_t i = money.size_; i > 0; --i) {
            if (i == 2) {
                os << '.';
            }
            T digit = money.data_[i - 1];
            os << static_cast<int>(digit);
        }
    }

    return os;
}


void Money::reserve(size_t cap) {
    if (cap <= size_) {
        return;
    }

    T* new_data = new T[cap];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
}

void Money::Normalize() {
    T carry = 0;
    for (size_t i = 0; i < size_; ++i) {
        data_[i] += carry;
        if (data_[i] >= 10) {
            carry = data_[i] / 10;
            data_[i] %= 10;
        } else {
            carry = 0;
        }
    }

    while (carry > 0) {
        push_back(carry % 10);
        carry /= 10;
    }

    while (size_ > 1 && data_[size_ - 1] == 0) {
        --size_;
    }
}

void Money::Normalize(Money& money) const {
    T carry = 0;
    for (size_t i = 0; i < money.size_; ++i) {
        money.data_[i] += carry;
        if (money.data_[i] >= 10) {
            carry = money.data_[i] / 10;
            money.data_[i] %= 10;
        } else {
            carry = 0;
        }
    }

    while (carry > 0) {
        money.push_back(carry % 10);
        carry /= 10;
    }

    while (money.size_ > 1 && money.data_[money.size_ - 1] == 0) {
        --money.size_;
    }
}


Money::~Money() {
    delete[] data_;
    
}