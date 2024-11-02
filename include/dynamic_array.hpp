#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <memory>
#include <iterator>
#include <memory_resource>

template <class T>
class DynamicArray {
public:
    using allocator = std::pmr::polymorphic_allocator<T>;

    explicit DynamicArray(std::pmr::memory_resource* mr = std::pmr::get_default_resource());

    ~DynamicArray();

    void push_back(const T& value);

    void pop_back();

    void clear();

    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::size_t capacity() const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;


    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(pointer ptr);

        reference operator*() const;

        pointer operator->() { return ptr_; }

        Iterator& operator++();

        Iterator operator++(int);

        friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr_ == b.ptr_; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr_ != b.ptr_; }

    private:
        pointer ptr_;
    };

    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }

private:
    void reserve(std::size_t new_capacity);

    allocator alloc_;
    T*data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};

#include "dynamic_array.hpp"

template<class T>
DynamicArray<T>::DynamicArray(std::pmr::memory_resource* mr)
        : alloc_(mr), data_(nullptr), size_(0), capacity_(0) {}

template<class T>
DynamicArray<T>::~DynamicArray() {
    clear();
    alloc_.deallocate(data_, capacity_);
}

template<class T>
void DynamicArray<T>::push_back(const T &value) {
    if (size_ >= capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    alloc_.construct(data_ + size_, value);
    ++size_;
}

template<class T>
void DynamicArray<T>::pop_back() {
    if (size_ > 0) {
        --size_;
        alloc_.destroy(data_ + size_);
    }
}

template<class T>
void DynamicArray<T>::clear() {
    for (std::size_t i = 0; i < size_; ++i) {
        alloc_.destroy(data_ + i);
    }
    size_ = 0;
}

template<class T>
std::size_t DynamicArray<T>::size() const {
    return size_;
}

template<class T>
std::size_t DynamicArray<T>::capacity() const {
    return capacity_;
}

template<class T>
T & DynamicArray<T>::operator[](std::size_t index) {
    return data_[index];
}

template<class T>
const T & DynamicArray<T>::operator[](std::size_t index) const {
    return data_[index];
}

template<class T>
DynamicArray<T>::Iterator::Iterator(pointer ptr): ptr_(ptr) {
}

template<class T>
typename DynamicArray<T>::Iterator::reference DynamicArray<T>::Iterator::operator*() const { return *ptr_; }

template<class T>
typename DynamicArray<T>::Iterator & DynamicArray<T>::Iterator::operator++() {
    ++ptr_;
    return *this;
}

template<class T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}


template<class T>
void DynamicArray<T>::reserve(std::size_t new_capacity) {
    T* new_data = alloc_.allocate(new_capacity);
    try {
        std::uninitialized_move(data_, data_ + size_, new_data);
    } catch (...) {
        alloc_.deallocate(new_data, new_capacity);
        throw;
    }
    std::destroy(data_, data_ + size_);
    alloc_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = new_capacity;
}

#endif //DYNAMIC_ARRAY_HPP
