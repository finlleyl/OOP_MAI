#ifndef FIGUREARRAY_H
#define FIGUREARRAY_H

#include "figure.h"

class FigureArray {
public:
    FigureArray();

    ~FigureArray();

    void Add(Figure *figure);

    void Remove(size_t index);

    Figure *Get(size_t index) const;

    size_t Size() const;

    double TotalArea() const;

private:
    Figure **data;
    size_t capacity;
    size_t count;

    void Resize(size_t newCapacity);
};

#endif // FIGUREARRAY_H
