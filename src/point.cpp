#include "point.h"

template <Number T>
T Point<T>::getX() const {
    return x;
}

template <Number T>
T Point<T>::getY() const {
    return y;
}

template <Number T>
void Point<T>::setX(T xVal) {
    x = xVal;
}

template <Number T> 
void Point<T>::setY(T yVal) {
    y = yVal;
}

template <Number T>
bool Point<T>::operator==(const Point<T>& other) const {
    return x == other.x && y == other.y;
}