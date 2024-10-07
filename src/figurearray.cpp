#include "figurearray.h"
#include <stdexcept>

FigureArray::FigureArray() : data(nullptr), capacity(0), count(0) {
}

FigureArray::~FigureArray() {
    for (size_t i = 0; i < count; ++i) {
        delete data[i];
    }
    delete[] data;
}

void FigureArray::Add(Figure *figure) {
    if (count == capacity) {
        Resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[count++] = figure;
}

void FigureArray::Remove(size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    delete data[index];
    for (size_t i = index; i < count - 1; ++i) {
        data[i] = data[i + 1];
    }
    --count;
}

Figure *FigureArray::Get(size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

size_t FigureArray::Size() const {
    return count;
}

void FigureArray::Resize(size_t newCapacity) {
    Figure **newData = new Figure *[newCapacity];
    for (size_t i = 0; i < count; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

double FigureArray::TotalArea() const {
    double totalArea = 0;
    for (size_t i = 0; i < count; ++i) {
        if (data[i] != nullptr) {
            totalArea += static_cast<double>(*data[i]);
        }
    }
    return totalArea;
}
