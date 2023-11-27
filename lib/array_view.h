#pragma once

#include <stddef.h>
#include <cstdint>
#include <stdexcept>
#include "array.h"

namespace uint17 {

class ArrayView {
 public:
  ArrayView(Array& array);
  ArrayView(Array& array, size_t start, size_t end);
  UInt17View operator[](size_t index);
  const UInt17View operator[](size_t index) const;
  size_t GetLength() const;
  UInt17View Get(size_t index);
  const UInt17View Get(size_t index) const;
 private:
  Array* const array_;
  size_t start_;
  size_t end_;
};

} // namespace uint17
