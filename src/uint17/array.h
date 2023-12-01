#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <concepts>
#include "uint17_view.h"
#include "utils.h"

namespace uint17 {

template <typename T>
concept NumberView = std::constructible_from<T, uint8_t*, size_t> && requires(T n, uint32_t v) {
  { T::kBitLength } -> std::same_as<const size_t&>;
  n = v;
};

template <NumberView View = UInt17View>
class Array {
 public:
  explicit Array(size_t length): length_(length) {
    const auto length_in_bits = length * View::kBitLength;
    length_in_bytes_ = (length_in_bits % 8 == 0) ? length_in_bits / 8 : length_in_bits / 8 + 1;
    data_ = new uint8_t[length_in_bytes_];
  }
  Array(std::initializer_list<uint32_t> elems): length_(elems.size()) {
    const auto length_in_bits = length_ * View::kBitLength;
    length_in_bytes_ = (length_in_bits % 8 == 0) ? length_in_bits / 8 : length_in_bits / 8 + 1;
    data_ = new uint8_t[length_in_bytes_];

    size_t i = 0;
    for (uint32_t elem : elems) {
      const auto start_of_number = i * View::kBitLength;
      View(data_ + start_of_number / 8, start_of_number % 8) = elem;
      ++i;
    }
  }
  ~Array() {
    delete[] data_;
  }
  Array(Array&& other): length_in_bytes_(other.length_in_bytes_), length_(other.length_) {
    data_ = other.data_;
    other.data_ = nullptr;
    other.length_ = 0;
    other.length_in_bytes_ = 0;
  }
  Array(const Array& other): Array(other.length_) {
    // std::memcpy(data_, other.data_, length_);  Not allowed to use memcpy by TA. But why???
    for (size_t i = 0; i != length_in_bytes_; ++i) {
      data_[i] = other.data_[i];
    }
  }
  Array& operator=(const Array& other) {
    if (this == &other) {
      return *this;
    }

    Array copy(other);
    utils::Swap(*this, copy);

    return *this;
  }
  Array& operator=(Array&& other) {
    utils::Swap(data_, other.data_);
    utils::Swap(length_, other.length_);
    utils::Swap(length_in_bytes_, other.length_in_bytes_);

    return *this;
  }
  [[nodiscard]] size_t size() const { return length_; }
  View operator[](size_t index) {
    const auto start_of_number = index * View::kBitLength;

    return View(data_ + start_of_number / 8, start_of_number % 8);
  }
  const View operator[](size_t index) const {
    const auto start_of_number = index * View::kBitLength;

    return View(data_ + start_of_number / 8, start_of_number % 8);
  }
  View At(size_t index) {
    if (index >= length_) {
      throw std::out_of_range("Array::at");
    }

    return this->operator[](index);
  }
  const View At(size_t index) const {
    if (index >= length_) {
      throw std::out_of_range("Array::at");
    }

    return this->operator[](index);
  }
 private:
  uint8_t* data_;
  size_t length_in_bytes_;
  size_t length_;
};

}  // namespace uint17
