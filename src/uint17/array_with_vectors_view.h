#pragma once

#include "array_view.h"

namespace uint17 {

template<typename T>
concept RandomAccessContainerWithVectors = RandomAccessContainer<T> && requires(T t, size_t index, uint32_t lambda) {
  t[index] *= lambda;
  t[index] += t[index];
  t[index] -= t[index];
};

template <size_t Dimension, RandomAccessContainerWithVectors Container>
struct VectorsViewWithContainer;

template <size_t Dimension, RandomAccessContainerWithVectors Container = Array<UInt17View>>
class ArrayWithVectorsView: public ArrayView<Dimension, Container> {
 public:
  using ArrayView<Dimension, Container>::ArrayView;
  VectorsViewWithContainer<Dimension, Container> operator*(uint32_t lambda) {
    auto container = new Container(this->container_.size() - this->start_);
    for (size_t i = 0; i != this->end_ - this->start_; ++i) {
      container->operator[](i) = this->container_[this->start_ + i];
      container->operator[](i) *= lambda;
    }
    auto view = ArrayWithVectorsView(*container, 0, this->dimensions_);

    return {view, container};
  }
  VectorsViewWithContainer<Dimension, Container> operator+(const ArrayWithVectorsView<Dimension, Container>& other) {
    for (size_t i = 0; i != Dimension; ++i) {
      if (this->dimensions_[i] != other.dimensions_[i]) {
        throw std::logic_error("ArrayView::operator+ different dimensions used");
      }
    }
    auto container = new Container(this->container_.size() - this->start_);
    for (size_t i = 0; i != this->end_ - this->start_; ++i) {
      container->operator[](i) = this->container_[this->start_ + i];
      container->operator[](i) += other.container_[other.start_ + i];
    }
    auto view = ArrayWithVectorsView(*container, 0, this->dimensions_);

    return {view, container};
  }
  VectorsViewWithContainer<Dimension, Container> operator-(const ArrayWithVectorsView<Dimension, Container>& other) {
    for (size_t i = 0; i != Dimension; ++i) {
      if (this->dimensions_[i] != other.dimensions_[i]) {
        throw std::logic_error("ArrayView::operator+ different dimensions used");
      }
    }
    auto container = new Container(this->container_.size() - this->start_);
    for (size_t i = 0; i != this->end_ - this->start_; ++i) {
      container->operator[](i) = this->container_[this->start_ + i];
      container->operator[](i) -= other.container_[other.start_ + i];
    }
    auto view = ArrayWithVectorsView(*container, 0, this->dimensions_);

    return {view, container};
  }
  template <typename... Args> requires Dimensions<Dimension, Args...>
  static VectorsViewWithContainer<Dimension, Container> MakeArray(Args... args) {
    auto container = new Container((args * ...));
    auto view = ArrayWithVectorsView(*container, 0, args...);

    return {view, container};
  }
};

template <RandomAccessContainerWithVectors Container>
class ArrayWithVectorsView<1, Container>: public ArrayView<1, Container> {
 public:
  using ArrayView<1, Container>::ArrayView;
  VectorsViewWithContainer<1, Container> operator*(uint32_t lambda) {
    auto container = new Container(this->container_.size() - this->start_);
    for (size_t i = 0; i != this->end_ - this->start_; ++i) {
      container->operator[](i) = this->container_[this->start_ + i];
      container->operator[](i) *= lambda;
    }
    auto view = ArrayWithVectorsView<1, Container>(*container, 0, this->end_ - this->start_);

    return {view, container};
  }
  VectorsViewWithContainer<1, Container> operator+(const ArrayWithVectorsView<1, Container>& other) {
    if (this->GetLength() != other.GetLength()) throw std::logic_error("ArrayView::operator+, they are not same length");
    auto container = new Container(this->container_.size() - this->start_);
    for (size_t i = 0; i != this->end_ - this->start_; ++i) {
      container->operator[](i) = this->container_[this->start_ + i];
      container->operator[](i) += other.container_[other.start_ + i];
    }
    auto view = ArrayWithVectorsView<1, Container>(*container, 0, this->end_ - this->start_);

    return {view, container};
  }
  VectorsViewWithContainer<1, Container> operator-(const ArrayWithVectorsView<1, Container>& other) {
    if (this->GetLength() != other.GetLength()) throw std::logic_error("ArrayView::operator-, they are not same length");
    auto container = new Container(this->container_.size() - this->start_);
    for (size_t i = 0; i != this->end_ - this->start_; ++i) {
      container->operator[](i) = this->container_[this->start_ + i];
      container->operator[](i) -= other.container_[other.start_ + i];
    }
    auto view = ArrayWithVectorsView<1, Container>(*container, 0, this->end_ - this->start_);

    return {view, container};
  }

  static VectorsViewWithContainer<1, Container> MakeArray(size_t length) {
    auto container = new Container(length);
    auto view = ArrayWithVectorsView<1, Container>(*container, 0, length);

    return {view, container};
  }
};

template <size_t Dimension, RandomAccessContainerWithVectors Container>
struct VectorsViewWithContainer {
  ArrayWithVectorsView<Dimension, Container> view;
  Container* container;
};

}  // namespace uint17

template <size_t Dimension, uint17::RandomAccessContainer Container>
std::ostream& operator<<(std::ostream& stream, const uint17::ArrayWithVectorsView<Dimension, Container>& view) {
  Container& data = view.GetContainer();
  for (size_t i = view.GetStart(); i != data.size() - 1; ++i) {
    stream << data[i] << " ";
  }
  stream << data[data.size() - 1];

  return stream;
}

template <size_t Dimension, uint17::RandomAccessContainer Container>
std::istream& operator>>(std::istream& stream, uint17::ArrayWithVectorsView<Dimension, Container>& view) {
  Container& data = view.GetContainer();
  for (size_t i = view.GetStart(); i != data.size(); ++i) stream >> data[i];

  return stream;
}