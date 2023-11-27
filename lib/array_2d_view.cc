#include "array_2d_view.h"

namespace uint17 {

Array2DView::Array2DView(Array& array, size_t start, size_t width, size_t length):
  array_(&array), start_(start), end_(start + width * length), width_(width), length_(length) {
  if (end_ > array.GetLength()) {
    throw std::out_of_range("Array2DView::Array2DView given offset + length > array length");
  }
}

ArrayView Array2DView::operator[](size_t index) {
  return ArrayView(*array_, start_ + width_ * index, start_ + width_ * (index + 1));
}

const ArrayView Array2DView::operator[](size_t index) const {
  return ArrayView(*array_, start_ + width_ * index, start_ + width_ * (index + 1));
}

size_t Array2DView::GetLength() { return length_; }

size_t Array2DView::GetWidth() { return width_; }

UInt17View Array2DView::Get(size_t i, size_t j) {
  return array_->operator[](i * width_ + j);
}

const UInt17View Array2DView::Get(size_t i, size_t j) const {
  return const_cast<const Array* const>(array_)->operator[](i * width_ + j);
}  

} // namespace uint17
