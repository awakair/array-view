#pragma once

#include "Array.h"
#include <iostream>
#include <cstdint>

class Array3DView {
 public:
  Array3DView(size_t height, size_t width, size_t length);
 private:
  Array data_;
};
