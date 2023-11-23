#include "Array.h"
#include "UInt17View.h"

Array::Array(size_t length) : length_(length) {
  data_ = new uint8_t[length];
}

Array::~Array() {
  if (data_ != nullptr) delete[] data_;
}

Array::Array(Array&& other): length_(other.length_) {
  data_ = other.data_;
  other.data_ = nullptr;
  other.length_ = 0;
}
Array::Array(Array& other): length_(other.length_) {
  data_ = new uint8_t[length_];
  std::memcpy(data_, other.data_, length_);
}

Array& Array::operator=(const Array& other) {
  if (length_ != other.length_) {
    if (data_ != nullptr) delete[] data_;
    data_ = new uint8_t[other.length_];
    length_ = other.length_;
  }
  
  std::memcpy(data_, other.data_, length_);
  return *this;
}
Array& Array::operator=(Array&& other) {
  std::swap(data_, other.data_);
  std::swap(length_, other.length_);
  return *this;
}

size_t Array::GetLength() { return length_; };

UInt17View Array::operator[](size_t index) {
  size_t start_of_number = 17 * index;
  return UInt17View(data_ + start_of_number / 8, start_of_number % 8);
}
