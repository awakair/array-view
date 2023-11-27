#include "array_view.h"

namespace uint17 {

ArrayView::ArrayView(Array& array) : array_(&array), start_(0), end_(array.GetLength() - 1) {}

ArrayView::ArrayView(Array& array, size_t start, size_t end) :
  array_(&array), start_(start), end_(end) {
  if (end > array.GetLength()) {
    throw std::out_of_range("ArrayView::ArrayView given offset + length > array length");
  }
  if (start > end) {
    throw std::logic_error("ArrrayView::ArrayView start > end");
  }
}

UInt17View ArrayView::operator[](size_t index) {
   if (start_ + index >= end_) throw std::out_of_range("ArrayView::at");

  return array_->operator[](start_ + index);
}

const UInt17View ArrayView::operator[](size_t index) const {
  if (start_ + index >= end_) throw std::out_of_range("ArrayView::at");

  return const_cast<const Array* const>(array_)->operator[](start_ + index);
}

size_t ArrayView::GetLength() const { return end_ - start_; }

UInt17View ArrayView::Get(size_t index) {
  return array_->operator[](start_ + index);
}

const UInt17View ArrayView::Get(size_t index) const {
  return const_cast<const Array* const>(array_)->operator[](start_ + index);
}

} // namespace uint17
