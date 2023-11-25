#pragma once

#include <stddef.h>
#include <cstdint>
#include <algorithm>
#include "UInt17View.h"
#include "utils.h" // TODO(awakair): rename files to math google code style

class Array {
 public:
  explicit Array(size_t length);
  ~Array();
  Array(Array&& other);
  Array(Array& other);
  Array& operator=(const Array& other);
  Array& operator=(Array&& other);
  size_t GetLength();
  UInt17View operator[](size_t index);
  
 private:
  uint8_t* data_;
  size_t length_in_bytes_;
  size_t length_;
};
