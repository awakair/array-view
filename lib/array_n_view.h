#pragma once

#include <stddef.h>
#include <cstdint>
#include "array.h"
#include "uint17_view.h"

namespace uint17 {

template <size_t Dimension>
class ArrayView {
 public:
  template <std::same_as<size_t>...Args> requires (sizeof...(Args) == Dimension)
  ArrayView(Array& array, Args... dimensions);
  ArrayView<Dimension - 1> operator[](size_t index);
  const ArrayView<Dimension - 1> operator[](size_t index) const;
  size_t GetDimension(size_t index);
  template <std::same_as<size_t>...Args> requires (sizeof...(Args) == Dimension)
  UInt17View Get(Args... dimensions);
  template <std::same_as<size_t>...Args> requires (sizeof...(Args) == Dimension)
  const UInt17View Get(Args... dimensions) const;
 private:
  Array* const array_;
  size_t start_;
  size_t length_;
  size_t dimensions_[Dimension];
};

template <>
class ArrayView<1> { };
  
} // namespace uint17
