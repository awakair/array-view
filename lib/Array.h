#pragma once

#include <stddef.h>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include "UInt17View.h"

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
  size_t length_;
};
