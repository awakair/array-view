#include "array.h"

namespace uint17 {

Array::Array(size_t length) : length_(length) {
  const auto length_in_bits = length * 17;
  length_in_bytes_ = (length_in_bits % 8 == 0) ? length_in_bits / 8 : length_in_bits / 8 + 1;
  data_ = new uint8_t[length_in_bytes_];
}

Array::Array(std::initializer_list<uint32_t> elems) : length_(elems.size()) {
  const auto length_in_bits = length_ * 17;
  length_in_bytes_ = (length_in_bits % 8 == 0) ? length_in_bits / 8 : length_in_bits / 8 + 1;
  data_ = new uint8_t[length_in_bytes_];

  size_t i = 0;
  for (uint32_t elem : elems) {
    const auto start_of_number = i * 17;
    UInt17View(data_ + start_of_number / 8, start_of_number % 8) = elem;
    ++i;
  }
}

Array::~Array() {
  delete[] data_;
}

Array::Array(Array&& other) : length_in_bytes_(other.length_in_bytes_), length_(other.length_) {
  data_ = other.data_;
  other.data_ = nullptr;
  other.length_ = 0;
  other.length_in_bytes_ = 0;
}
Array::Array(const Array& other) : Array(other.length_) {
  // std::memcpy(data_, other.data_, length_);  Not allowed to use memcpy by TA. But why???
  for (size_t i = 0; i != length_in_bytes_; ++i) data_[i] = other.data_[i];
}

Array& Array::operator=(const Array& other) {
  if (this == &other) {
    return *this;
  }

  Array copy(other);
  utils::Swap(*this, copy);

  return *this;
}
Array& Array::operator=(Array&& other) {
  utils::Swap(data_, other.data_);
  utils::Swap(length_, other.length_);
  utils::Swap(length_in_bytes_, other.length_in_bytes_);

  return *this;
}

size_t Array::size() const { return length_; }

UInt17View Array::operator[](size_t index) {
  const auto start_of_number = index * 17;

  return UInt17View(data_ + start_of_number / 8, start_of_number % 8);
}

const UInt17View Array::operator[](size_t index) const {
  const auto start_of_number = index * 17;

  return UInt17View(data_ + start_of_number / 8, start_of_number % 8);
}

UInt17View Array::At(size_t index) {
  if (index >= length_) {
    throw std::out_of_range("Array::at");
  }

  return this->operator[](index);
}

const UInt17View Array::At(size_t index) const {
  if (index >= length_) {
    throw std::out_of_range("Array::at");
  }

  return this->operator[](index);
}

}  // namespace uint17
