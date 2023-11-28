#pragma once

#include <stddef.h>
#include <cstdint>
#include <concepts>
#include "array.h"
#include "uint17_view.h"

namespace uint17 {

namespace concepts {
template <typename T>
concept IsSize = std::same_as<size_t, T>;
template <size_t Dimension, typename... Args>
concept IsDimensions = ((IsSize<Args> && ...) && sizeof...(Args) == Dimension);
}

template <size_t Dimension>
class ArrayView {
 public:
  template <typename... Args> requires concepts::IsDimensions<Dimension, Args...>
  ArrayView(Array& array, size_t start, Args... dimensions): array_(&array), start_(start) {
    size_t i = 0;
    ((dimensions_[i++] = dimensions), ...);
    end_ = start_ + (dimensions * ...);
    if (end_ > array.GetLength()) {
      throw std::out_of_range("ArrayView::ArrayView, view with given dimensions end after array end");
    }
  }
  ArrayView(Array& array, size_t start, size_t* dimensions): array_(&array), start_(start) {
    size_t product = 1;
    for (size_t i = 0; i != Dimension; ++i) {
      dimensions_ = dimensions[i];
      product *= dimensions[i];
    }
    end_ = start_ + product;
    if (end_ > array.GetLength()) {
      throw std::out_of_range("ArrayView::ArrayView, view with given dimensions end after array end");
    }
  }
  
  ArrayView<Dimension - 1> operator[](size_t index) {
    return ArrayView<Dimension - 1>(*array_, start_ + dimensions_[0] * index, dimensions_ + 1);
  }
  const ArrayView<Dimension - 1> operator[](size_t index) const {
    return ArrayView<Dimension - 1>(*array_, start_ + dimensions_[0] * index, dimensions_ + 1);
  }
  
  size_t GetDimension(size_t index) const { return dimensions_[index]; }
  
  template <typename... Args> requires concepts::IsDimensions<Dimension, Args...>
  UInt17View Get(Args... dimensions) {
    size_t arguments[] = {(dimensions)...};
    size_t real_index = start_;
    for (size_t i = 0; i != Dimension - 1; ++i) {
      real_index += arguments[i] * dimensions_[i];
    }
    real_index += arguments[Dimension - 1];
    return array_->operator[](real_index);
  }
  template <typename...Args> requires concepts::IsDimensions<Dimension, Args...>
  const UInt17View Get(Args... dimensions) const {
    size_t arguments[] = {(dimensions)...};
    size_t real_index = start_;
    for (size_t i = 0; i != Dimension - 1; ++i) {
      real_index += arguments[i] * dimensions_[i];
    }
    real_index += arguments[Dimension - 1];
    return const_cast<const Array* const>(array_)->operator[](real_index);
  }
 private:
  Array* const array_;
  size_t start_;
  size_t end_;
  size_t dimensions_[Dimension];
};

template <>
class ArrayView<1> {
 public:
  ArrayView(Array& array): array_(&array), start_(0), end_(array.GetLength() - 1) {}
  ArrayView(Array& array, size_t start, size_t* end): ArrayView(array, start, start + *end) {}
  ArrayView(Array& array, size_t start, size_t end): array_(&array), start_(start), end_(end) {
    if (end > array.GetLength()) {
      throw std::out_of_range("ArrayView::ArrayView given offset + length > array length");
    }
    if (start > end) {
      throw std::logic_error("ArrrayView::ArrayView start > end");
    }
  }
  
  UInt17View operator[](size_t index)  {
   if (start_ + index >= end_) throw std::out_of_range("ArrayView::operator[]");
   return array_->operator[](start_ + index);
  }
  const UInt17View operator[](size_t index) const {
  if (start_ + index >= end_) throw std::out_of_range("ArrayView::operator[]");

  return const_cast<const Array* const>(array_)->operator[](start_ + index);
  }

  size_t GetLength() const { return end_ - start_; }
  UInt17View Get(size_t index) { return array_->operator[](start_ + index); }
  const UInt17View Get(size_t index) const {
    return const_cast<const Array* const>(array_)->operator[](start_ + index);
  }
 private:
  Array* const array_;
  size_t start_;
  size_t end_;
};
  
} // namespace uint17
