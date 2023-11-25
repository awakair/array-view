#pragma once

#include <_types/_uint32_t.h>
#include <initializer_list>
#include <stddef.h>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include "uint17_view.h"
#include "utils.h" // TODO(awakair): rename files to math google code style

namespace uint17 {

class Array {
 public:
  explicit Array(size_t length);
  Array(std::initializer_list<uint32_t> elems);
  ~Array();
  Array(Array&& other);
  Array(const Array& other);
  Array& operator=(const Array& other);
  Array& operator=(Array&& other);
  size_t GetLength() const;
  UInt17View operator[](size_t index);
  const UInt17View operator[](size_t index) const;
  UInt17View At(size_t index);
  const UInt17View At(size_t index) const;
 private:
  uint8_t* data_;
  size_t length_in_bytes_;
  size_t length_;
};

} // namespace uint17
