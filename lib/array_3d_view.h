#pragma once

#include "array.h"
#include <iostream>
#include <cstdint>

namespace uint17 {

class Array3DView {
 public:
  Array3DView(size_t height, size_t width, size_t length);
 private:
  Array data_;
};

} // namespace uin17
