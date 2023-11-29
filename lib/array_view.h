#pragma once

#include <cstddef>
#include <cstdint>
#include <concepts>
#include <exception>
#include "array.h"
#include "uint17_view.h"
#include "utils.h"

namespace uint17 {

namespace concepts {
  template <typename T>
  concept IsSize = std::same_as<size_t, T>;
  template <size_t Dimension, typename... Args>
  concept IsDimensions = ((IsSize<Args> && ...) && sizeof...(Args) == Dimension);
  template <typename T>
  concept IsRandomAccessContainer = std::constructible_from<T, size_t> && requires(T t, size_t index) {
    t[index];
    t[index] = t[index];
    { t.size() } -> std::same_as<size_t>;
  };
  template <typename T>
  concept IsRandomAccessContainerWithVectors = IsRandomAccessContainer<T> && requires(T t, size_t index, uint32_t lambda) {
    t[index] *= lambda;
    t[index] += t[index];
    t[index] -= t[index];
  };
}

template <size_t Dimension, concepts::IsRandomAccessContainer Container>
struct ViewWithContainer;


template <size_t Dimension, concepts::IsRandomAccessContainer Container = Array>
class ArrayView {
 public:
  template <typename... Args> requires concepts::IsDimensions<Dimension, Args...>
  ArrayView(Container& container, size_t start, Args... dimensions):
  container_(&container), start_(start), end_(start_ + (dimensions * ...)), dimensions_{(dimensions)...} {
    if (end_ > container.size()) {
      throw std::out_of_range("ArrayView::ArrayView, view with given dimensions end after container end");
    }
  }
  ArrayView(Container& container, size_t start, const size_t* dimensions): container_(&container), start_(start) {
    size_t product = 1;
    for (size_t i = 0; i != Dimension; ++i) {
      dimensions_[i] = dimensions[i];
      product *= dimensions[i];
    }
    end_ = start_ + product;
    if (end_ > container.size()) {
      throw std::out_of_range("ArrayView::ArrayView, view with given dimensions end after container end");
    }
  }

  ArrayView<Dimension - 1, Container> operator[](size_t index) {
    return ArrayView<Dimension - 1, Container>(*container_, start_ + dimensions_[0] * index, dimensions_ + 1);
  }
  const ArrayView<Dimension - 1, Container> operator[](size_t index) const {
    return ArrayView<Dimension - 1, Container>(*container_, start_ + dimensions_[0] * index, dimensions_ + 1);
  }

  [[nodiscard]] size_t GetDimension(size_t index) const { return dimensions_[index]; }
  [[nodiscard]] Container& GetContainer() const { return *container_; }

  template <typename... Args> requires concepts::IsDimensions<Dimension, Args...>
  decltype(auto) Get(Args... dimensions){
    size_t arguments[] = {(dimensions)...};
    size_t real_index = start_;
    for (size_t i = 0; i != Dimension - 1; ++i) {
      real_index += arguments[i] * dimensions_[i];
    }
    real_index += arguments[Dimension - 1];

    return container_->operator[](real_index);
  }
  template <typename...Args> requires concepts::IsDimensions<Dimension, Args...>
  decltype(auto) Get(Args... dimensions) const {
    size_t arguments[] = {(dimensions)...};
    size_t real_index = start_;
    for (size_t i = 0; i != Dimension - 1; ++i) {
      real_index += arguments[i] * dimensions_[i];
    }
    real_index += arguments[Dimension - 1];

    return const_cast<const Container* const>(container_)->operator[](real_index);
  }

  // useless methods
  ViewWithContainer<Dimension, Container> operator*(uint32_t lambda) requires concepts::IsRandomAccessContainerWithVectors<Container> {
    auto container = new Container(container_->size() - start_);
    for (size_t i = 0; i != end_ - start_; ++i) {
      container->operator[](i) = container_->operator[](start_ + i);
      container->operator[](i) *= lambda;
    }
    auto view = ArrayView(*container, 0, dimensions_);

    return {view, container};
  }
  ViewWithContainer<Dimension, Container> operator+(const ArrayView<Dimension, Container>& other) requires concepts::IsRandomAccessContainerWithVectors<Container> {
    for (size_t i = 0; i != Dimension; ++i) {
      if (dimensions_[i] != other.dimensions_[i]) {
        throw std::logic_error("ArrayView::operator+ different dimensions used");
      }
    }
    auto container = new Container(container_->size() - start_);
    for (size_t i = 0; i != end_ - start_; ++i) {
      container->operator[](i) = container_->operator[](start_ + i);
      container->operator[](i) += other.dimensions_[other.start_ + i];
    }
    auto view = ArrayView(*container, 0, dimensions_);

    return {view, container};
  }
  ViewWithContainer<Dimension, Container> operator-(const ArrayView<Dimension, Container>& other) requires concepts::IsRandomAccessContainerWithVectors<Container> {
    for (size_t i = 0; i != Dimension; ++i) {
      if (dimensions_[i] != other.dimensions_[i]) {
        throw std::logic_error("ArrayView::operator+ different dimensions used");
      }
    }
    auto container = new Container(container_->size() - start_);
    for (size_t i = 0; i != end_ - start_; ++i) {
      container->operator[](i) = container_->operator[](start_ + i);
      container->operator[](i) -= other.dimensions_[other.start_ + i];
    }
    auto view = ArrayView(*container, 0, dimensions_);

    return {view, container};
  }
  template <typename... Args> requires concepts::IsDimensions<Dimension, Args...>
  static ViewWithContainer<Dimension, Container> MakeArray(Args... args) {
    auto container = new Container((args * ...));
    auto view = ArrayView(*container, 0, args...);

    return {view, container};
  }

 private:
  Container* const container_;
  size_t start_;
  size_t end_;
  size_t dimensions_[Dimension];
};

template <concepts::IsRandomAccessContainer Container>
class ArrayView<1, Container> {
 public:
  ArrayView(Container& container): container_(&container), start_(0), end_(container.size() - 1) {}
  ArrayView(Container& container, size_t start, const size_t* end): ArrayView(container, start, start + *end) {}
  ArrayView(Container& container, size_t start, size_t end): container_(&container), start_(start), end_(end) {
    if (end > container.size()) {
      throw std::out_of_range("ArrayView::ArrayView given offset + length > container length");
    }
    if (start > end) {
      throw std::logic_error("ArrrayView::ArrayView start > end");
    }
  }
  
  decltype(auto) operator[](size_t index) {
    if (start_ + index >= end_) throw std::out_of_range("ArrayView::operator[]");

    return container_->operator[](start_ + index);
  }
  decltype(auto) operator[](size_t index) const {
    if (start_ + index >= end_) throw std::out_of_range("ArrayView::operator[]");

    return const_cast<const Container* const>(container_)->operator[](start_ + index);
  }

  [[nodiscard]] size_t GetLength() const { return end_ - start_; }
  [[nodiscard]] Container& GetContainer() const { return *container_; }
  decltype(auto) Get(size_t index) { return container_->operator[](start_ + index); }
  decltype(auto) Get(size_t index) const {
    return const_cast<const Container* const>(container_)->operator[](start_ + index);
  }

  // useless methods
  ViewWithContainer<1, Container> operator*(uint32_t lambda) requires concepts::IsRandomAccessContainerWithVectors<Container> {
    auto container = new Container(container_->size() - start_);
    for (size_t i = 0; i != end_ - start_; ++i) {
      container->operator[](i) = container_->operator[](start_ + i);
      container->operator[](i) *= lambda;
    }
    auto view = ArrayView<1, Container>(*container, 0, end_ - start_);

    return {view, container};
  }
  ViewWithContainer<1, Container> operator+(const ArrayView<1, Container>& other) requires concepts::IsRandomAccessContainerWithVectors<Container> {
    auto container = new Container(container_->size() - start_);
    for (size_t i = 0; i != end_ - start_; ++i) {
      container->operator[](i) = container_->operator[](start_ + i);
      container->operator[](i) += other.dimensions_[other.start_ + i];
    }
    auto view = ArrayView<1, Container>(*container, 0, end_ - start_);

    return {view, container};
  }
  ViewWithContainer<1, Container> operator-(const ArrayView<1, Container>& other) requires concepts::IsRandomAccessContainerWithVectors<Container> {
    auto container = new Container(container_->size() - start_);
    for (size_t i = 0; i != end_ - start_; ++i) {
      container->operator[](i) = container_->operator[](start_ + i);
      container->operator[](i) -= other.dimensions_[other.start_ + i];
    }
    auto view = ArrayView<1, Container>(*container, 0, end_ - start_);

    return {view, container};
  }
  static ViewWithContainer<1, Container> MakeArray(size_t length) {
    auto container = new Container(length);
    auto view = ArrayView<1, Container>(*container, 0, length);

    return {view, container};
  }

 private:
  Container* const container_;
  size_t start_;
  size_t end_;
};

template <size_t Dimension, concepts::IsRandomAccessContainer Container>
struct ViewWithContainer {
  ArrayView<Dimension, Container> view;
  Container container;
};

}  // namespace uint17

template <size_t Dimension, uint17::concepts::IsRandomAccessContainer Container>
std::ostream& operator<<(std::ostream& stream, const uint17::ArrayView<Dimension, Container>& view) {
  Container& data = view.GetContainer();
  for (size_t i = 0; i != data.size() - 1; ++i) {
    stream << data[i] << " ";
  }
  stream << data[data.size() - 1];

  return stream;
}

template <size_t Dimension,uint17::concepts::IsRandomAccessContainer Container>
std::istream& operator>>(std::istream& stream, uint17::ArrayView<Dimension, Container>& view) {
  Container& data = view.GetContainer();
  for (size_t i = 0; i != data.size(); ++i) stream >> data[i];

  return stream;
}
