#ifndef CONCEPT_HPP
#define CONCEPT_HPP

#include <type_traits>

template <typename T>
concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

#endif // CONCEPT_HPP
