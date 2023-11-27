#pragma once

#include <stddef.h>
#include <cstdint>
#include "array.h"
#include "array_view.h"

namespace uint17 {

class Array2DView {
 public:
  Array2DView(Array& array, size_t start, size_t width, size_t length);
  ArrayView operator[](size_t index);
  const ArrayView operator[](size_t index) const;
  size_t GetLength();
  size_t GetWidth();
  UInt17View Get(size_t i, size_t j);
  const UInt17View Get(size_t i, size_t j) const;
 private:
  Array* const array_;
  size_t start_;
  size_t end_;
  size_t width_;
  size_t length_;
};

} // namespace uint17
