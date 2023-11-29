#pragma once

#include <utility>



namespace uint17::utils {

template <typename T>
void Swap(T& a, T& b) { // I am not allowed to use std::swap
  T tmp = std::move(a);
  a = std::move(b);
  b = std::move(tmp);
}

template <typename First, typename Second>
struct Pair {
  First first;
  Second second;
};

} // namespace uint17::utils
