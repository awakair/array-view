#include <stdexcept>
#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include <uint17/array.h>
#include <uint17/uint17_view.h>
#include <uint17/array_view.h>
#include <uint17/array_with_vectors_view.h>

using namespace uint17;

TEST(UInt17ViewTest, OffsetTest) {
  uint8_t data1[3];
  uint8_t data2[3];

  UInt17View number1(data1, 2);
  number1 = 25u;
  UInt17View number2(data2, 5);
  number2 = 1000u;

  ASSERT_EQ(number1.ToUInt32(), 25u);
  ASSERT_EQ(number2.ToUInt32(), 1000u);
}

TEST(UInt17ViewTest, FromUInt16Test) {
  uint16_t val = 32;
  uint8_t data[3];

  UInt17View number(data, 0);

  number = val;

  ASSERT_EQ(number.ToUInt32(), val);
}

TEST(UInt17ViewTest, FromUInt32Test) {
  uint32_t val = 65000;
  uint8_t data[3];

  UInt17View number(data, 0);

  number = val;

  ASSERT_EQ(number.ToUInt32(), val);
}

TEST(UInt17ViewTest, FromAnotherUInt17ViewTest) {
  uint32_t val = 65000;
  uint8_t data1[3];
  uint8_t data2[3];

  UInt17View number1(data1, 0);
  UInt17View number2(data2, 0);

  number1 = val;
  number2 = number1;

  ASSERT_EQ(number2.ToUInt32(), val);
}

TEST(UInt17ViewTest, SetToZeroTest) {
  uint32_t val = 65000;
  uint8_t data[3];

  UInt17View number(data, 0);

  number = val;
  number.SetToZero();

  ASSERT_EQ(number.ToUInt32(), 0);
}

TEST(UInt17ViewTest, PlusTest) {
  uint32_t val1 = 20;
  uint32_t val2 = 15;
  uint32_t val3 = 50;
  uint32_t val4 = 10;

  uint8_t data1[3];
  uint8_t data2[3];
  uint8_t data3[3];

  UInt17View number1(data1, 0);
  UInt17View number2(data2, 0);
  UInt17View number3(data3, 0);

  number1 = val1;
  number2 = val2;
  number3 = val3;

  number1 += number2;
  number3 += val4;

  ASSERT_EQ(number1.ToUInt32(), val1 + val2);
  ASSERT_EQ(number3.ToUInt32(), val3 + val4);
}

TEST(UInt17ViewTest, MinusTest) {
  uint32_t val1 = 20;
  uint32_t val2 = 15;
  uint32_t val3 = 50;
  uint32_t val4 = 10;

  uint8_t data1[3];
  uint8_t data2[3];
  uint8_t data3[3];

  UInt17View number1(data1, 0);
  UInt17View number2(data2, 0);
  UInt17View number3(data3, 0);

  number1 = val1;
  number2 = val2;
  number3 = val3;

  number1 -= number2;
  number3 -= val4;

  ASSERT_EQ(number1.ToUInt32(), val1 - val2);
  ASSERT_EQ(number3.ToUInt32(), val3 - val4);
}

TEST(UInt17ViewTest, MultTest) {
  uint32_t val1 = 20;
  uint32_t val2 = 15;
  uint32_t val3 = 50;
  uint32_t val4 = 10;

  uint8_t data1[3];
  uint8_t data2[3];
  uint8_t data3[3];

  UInt17View number1(data1, 0);
  UInt17View number2(data2, 0);
  UInt17View number3(data3, 0);

  number1 = val1;
  number2 = val2;
  number3 = val3;

  number1 *= number2;
  number3 *= val4;

  ASSERT_EQ(number1.ToUInt32(), val1 * val2);
  ASSERT_EQ(number3.ToUInt32(), val3 * val4);
}

TEST(ArrayTest, EmptyTest) {
  Array array(5);
}

TEST(ArrayTest, InitializerListTest) {
  const Array array = {1, 2, 3, 4, 5};

  ASSERT_EQ(array[0].ToUInt32(), 1);
  ASSERT_EQ(array[1].ToUInt32(), 2);
  ASSERT_EQ(array[2].ToUInt32(), 3);
  ASSERT_EQ(array[3].ToUInt32(), 4);
  ASSERT_EQ(array[4].ToUInt32(), 5);
}

TEST(ArrayTest, CopyConstructor) {
  const Array array1 = {1, 2, 3, 4, 5};
  const Array array2(array1);

  ASSERT_EQ(array1[0].ToUInt32(), array2[0].ToUInt32());
  ASSERT_EQ(array1[1].ToUInt32(), array2[1].ToUInt32());
  ASSERT_EQ(array1[2].ToUInt32(), array2[2].ToUInt32());
  ASSERT_EQ(array1[3].ToUInt32(), array2[3].ToUInt32());
  ASSERT_EQ(array1[4].ToUInt32(), array2[4].ToUInt32());
}

TEST(ArrayTest, MoveConstructor) {
  Array array1 = {1, 2, 3, 4, 5};
  Array array2(std::move(array1));

  ASSERT_EQ(array2[0].ToUInt32(), 1);
  ASSERT_EQ(array2[1].ToUInt32(), 2);
  ASSERT_EQ(array2[2].ToUInt32(), 3);
  ASSERT_EQ(array2[3].ToUInt32(), 4);
  ASSERT_EQ(array2[4].ToUInt32(), 5);
}

TEST(ArrayTest, CopyAssingmentOperator) {
  Array array1 = {1, 2, 3, 4, 5};
  Array array2(4);
  array2 = array1;

  ASSERT_EQ(array1[0].ToUInt32(), array2[0].ToUInt32());
  ASSERT_EQ(array1[1].ToUInt32(), array2[1].ToUInt32());
  ASSERT_EQ(array1[2].ToUInt32(), array2[2].ToUInt32());
  ASSERT_EQ(array1[3].ToUInt32(), array2[3].ToUInt32());
  ASSERT_EQ(array1[4].ToUInt32(), array2[4].ToUInt32());
}

TEST(ArrayTest, MoveAssingmentOperator) {
  Array array1 = {1, 2, 3, 4, 5};
  Array array2(4);
  array2 = std::move(array1);

  ASSERT_EQ(array2[0].ToUInt32(), 1);
  ASSERT_EQ(array2[1].ToUInt32(), 2);
  ASSERT_EQ(array2[2].ToUInt32(), 3);
  ASSERT_EQ(array2[3].ToUInt32(), 4);
  ASSERT_EQ(array2[4].ToUInt32(), 5);
}

TEST(ArrayTest, GetLengthTest) {
  ASSERT_EQ(Array(5).size(), 5);
  ASSERT_EQ(Array(19).size(), 19);
  ASSERT_EQ(Array(108).size(), 108);
  ASSERT_EQ(Array(504).size(), 504);
}

TEST(ArrayTest, SizeTest) {
  ASSERT_EQ(Array(5).size(), 5);
  ASSERT_EQ(Array(19).size(), 19);
  ASSERT_EQ(Array(108).size(), 108);
  ASSERT_EQ(Array(504).size(), 504);
}

TEST(ArrayTest, FillUInt32Test) {
  uint32_t val1 = 12;
  uint32_t val2 = 66000;
  uint32_t val3 = 0;

  Array array(3);
  array[0] = val1;
  array[1] = val2;
  array[2] = val3;

  ASSERT_EQ(array[0].ToUInt32(), val1);
  ASSERT_EQ(array[1].ToUInt32(), val2);
  ASSERT_EQ(array[2].ToUInt32(), val3);
}

TEST(ArrayTest, AtTest) {
  Array array = {1, 2, 3, 4};

  ASSERT_EQ(array.At(1).ToUInt32(), 2);
  ASSERT_THROW(array.At(4), std::out_of_range);
}

TEST(Array1DViewTest, EmptyTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView<1> view(array);
}

TEST(Array1DViewTest, WrongViewTest) {
  Array array = {1, 2, 3, 4, 5};

  ASSERT_ANY_THROW(ArrayView<1>(array, 0, 7));
}

TEST(Array1DViewTest, AccesToElementsTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView<1> view(array);

  view[0] = 20u;

  ASSERT_EQ(array[0].ToUInt32(), 20u);
  ASSERT_EQ(array[2].ToUInt32(), view[2].ToUInt32());
  ASSERT_ANY_THROW(view[10]);
}

TEST(Array1DViewTest, OffsetTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView<1> view(array, 1, 4);

  ASSERT_EQ(array[1].ToUInt32(), view[0].ToUInt32());
  ASSERT_ANY_THROW(view[4]);
}

TEST(Array1DViewTest, GetTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView<1> view(array);

  view.Get(0) = 20u;

  ASSERT_EQ(array[0].ToUInt32(), 20u);
  ASSERT_EQ(array[2].ToUInt32(), view.Get(2).ToUInt32());
}

TEST(Array1DViewTest, GetLengthTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView<1> view(array);


  ASSERT_EQ(array.size(), view.GetLength());
}

TEST(Array1DViewTest, GetContainerTest) {
  Array array = {1, 2, 3, 4, 5};
  ASSERT_EQ(&ArrayView<1>(array).GetContainer(), &array);
}

TEST(Array1DViewTest, MultTest) {
  Array array1 = {1, 2, 3, 4, 5};
  ArrayWithVectorsView<1> view(array1);
  uint32_t lambda = 2;
  auto [result, array] = view * lambda;
  ASSERT_EQ(result[0].ToUInt32(), view[0].ToUInt32() * lambda);
  ASSERT_EQ(result[1].ToUInt32(), view[1].ToUInt32() * lambda);
  ASSERT_EQ(result[2].ToUInt32(), view[2].ToUInt32() * lambda);
  ASSERT_EQ(result[3].ToUInt32(), view[3].ToUInt32() * lambda);
  ASSERT_EQ(result[4].ToUInt32(), view[4].ToUInt32() * lambda);
  ASSERT_NE(&result.GetContainer(), &view.GetContainer());
  delete array;
}

TEST(Array1DViewTest, PlusTest) {
  Array array1 = {1, 2, 3, 4, 5};
  Array array2 = {6, 7, 8, 9, 10};
  Array array3 = {1, 2};
  ArrayWithVectorsView<1> view1(array1);
  ArrayWithVectorsView<1> view2(array2);
  ArrayWithVectorsView<1> view3(array3);

  auto [result, array] = view1 + view2;

  ASSERT_ANY_THROW(view2 + view3);
  ASSERT_EQ(result[0].ToUInt32(), view1[0].ToUInt32() + view2[0].ToUInt32());
  ASSERT_EQ(result[1].ToUInt32(), view1[1].ToUInt32() + view2[1].ToUInt32());
  ASSERT_EQ(result[2].ToUInt32(), view1[2].ToUInt32() + view2[2].ToUInt32());
  ASSERT_EQ(result[3].ToUInt32(), view1[3].ToUInt32() + view2[3].ToUInt32());
  ASSERT_EQ(result[4].ToUInt32(), view1[4].ToUInt32() + view2[4].ToUInt32());
  ASSERT_NE(&result.GetContainer(), &view1.GetContainer());
  ASSERT_NE(&result.GetContainer(), &view2.GetContainer());
  delete array;
}

TEST(Array1DViewTest, MinusTest) {
  Array array1 = {6, 7, 8, 9, 10};
  Array array2 = {1, 2, 3, 4, 5};
  Array array3 = {1, 2};
  ArrayWithVectorsView<1> view1(array1);
  ArrayWithVectorsView<1> view2(array2);
  ArrayWithVectorsView<1> view3(array3);

  auto [result, array] = view1 - view2;

  ASSERT_ANY_THROW(view2 - view3);
  ASSERT_EQ(result[0].ToUInt32(), view1[0].ToUInt32() - view2[0].ToUInt32());
  ASSERT_EQ(result[1].ToUInt32(), view1[1].ToUInt32() - view2[1].ToUInt32());
  ASSERT_EQ(result[2].ToUInt32(), view1[2].ToUInt32() - view2[2].ToUInt32());
  ASSERT_EQ(result[3].ToUInt32(), view1[3].ToUInt32() - view2[3].ToUInt32());
  ASSERT_EQ(result[4].ToUInt32(), view1[4].ToUInt32() - view2[4].ToUInt32());
  ASSERT_NE(&result.GetContainer(), &view1.GetContainer());
  ASSERT_NE(&result.GetContainer(), &view2.GetContainer());
  delete array;
}

TEST(Array1DViewTest, MakeArrayTest) {
  auto [view, array] = ArrayView<1>::MakeArray(5);
  view[0] = 1u;
  view[1] = 2u;
  view[2] = 3u;
  view[3] = 4u;
  view[4] = 5u;

  ASSERT_EQ(array->At(0).ToUInt32(), 1u);
  ASSERT_EQ(array->At(1).ToUInt32(), 2u);
  ASSERT_EQ(array->At(2).ToUInt32(), 3u);
  ASSERT_EQ(array->At(3).ToUInt32(), 4u);
  ASSERT_EQ(array->At(4).ToUInt32(), 5u);
  delete array;
}

TEST(Array1DViewTest, InputTest) {
  std::string input = "1 2 3 4 5";
  std::stringstream input_stream(input);
  auto [view, array] = ArrayWithVectorsView<1>::MakeArray(5);
  input_stream >> view;
  ASSERT_EQ(view[0].ToUInt32(), 1u);
  ASSERT_EQ(view[1].ToUInt32(), 2u);
  ASSERT_EQ(view[2].ToUInt32(), 3u);
  ASSERT_EQ(view[3].ToUInt32(), 4u);
  ASSERT_EQ(view[4].ToUInt32(), 5u);
  delete array;
}

TEST(Array1DViewTest, OutputTest) {
  std::stringstream output_stream;
  Array array = {1, 2, 3, 4, 5};
  ArrayWithVectorsView<1> view(array);
  output_stream << view;
  ASSERT_EQ(output_stream.str(), "1 2 3 4 5");
}

TEST(Array2DViewTest, EmptyTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView<2> view(array, 0u, 2u, 2u);
}

TEST(Array2DViewTest, WrongViewTest) {
  Array array = {1, 2, 3};
  ASSERT_ANY_THROW(ArrayView<2>(array, 0, 2u, 2u));
}

TEST(Array2DViewTest, AccesToElementsTest) {
  Array array = {1, 2, 3, 4};
  ArrayView<2> view(array, 0, 2u, 2u);

  view[0][0] = 1u;
  view[0][1] = 2u;
  view[1][0] = 3u;
  view[1][1] = 4u;

  ASSERT_EQ(array[0].ToUInt32(), 1u);
  ASSERT_EQ(array[1].ToUInt32(), 2u);
  ASSERT_EQ(array[2].ToUInt32(), 3u);
  ASSERT_EQ(array[3].ToUInt32(), 4u);
  ASSERT_ANY_THROW(view[3][0]);
  ASSERT_ANY_THROW(view[0][3]);
}

TEST(Array2DViewTest, OffsetTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView<2> view(array, 1, 2u, 2u);

  view[0][0] = 1u;
  view[0][1] = 2u;
  view[1][0] = 3u;
  view[1][1] = 4u;

  ASSERT_EQ(array[1].ToUInt32(), 1u);
  ASSERT_EQ(array[2].ToUInt32(), 2u);
  ASSERT_EQ(array[3].ToUInt32(), 3u);
  ASSERT_EQ(array[4].ToUInt32(), 4u);
  ASSERT_ANY_THROW(view[3][0]);
  ASSERT_ANY_THROW(view[0][3]);
}

TEST(Array2DViewTest, GetTest) {
  Array array = {1, 2, 3, 4};
  ArrayView<2> view(array, 0, 2u, 2u);

  view.Get(0u, 0u) = 5u;

  ASSERT_EQ(array[0].ToUInt32(), 5u);
  ASSERT_EQ(array[2].ToUInt32(), view.Get(1u, 0u).ToUInt32());
}

TEST(Array2DViewTest, GetDimensionTest) {
  Array array = {1, 2, 3, 4, 5, 6};
  ArrayView<2> view(array, 0, 2u, 3u);

  ASSERT_EQ(view.GetDimension(0), 2u);
  ASSERT_EQ(view.GetDimension(1), 3u);
}

TEST(Array2DViewTest, GetContainerTest) {
  Array array = {1, 2, 3, 4, 5};
  ASSERT_EQ(&ArrayView<2>(array, 0, 2u, 2u).GetContainer(), &array);
}

TEST(Array2DViewTest, MultTest) {
  Array array1 = {1, 2, 3, 4, 5, 6};
  ArrayWithVectorsView<2> view(array1, 0, 2u, 3u);
  uint32_t lambda = 2;
  auto [result, array] = view * lambda;
  ASSERT_EQ(result.Get(0u, 0u).ToUInt32(), view.Get(0u, 0u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(0u, 1u).ToUInt32(), view.Get(0u, 1u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(0u, 2u).ToUInt32(), view.Get(0u, 2u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(1u, 0u).ToUInt32(), view.Get(1u, 0u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(1u, 1u).ToUInt32(), view.Get(1u, 1u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(1u, 2u).ToUInt32(), view.Get(1u, 2u).ToUInt32() * lambda);
  ASSERT_NE(&result.GetContainer(), &view.GetContainer());
  delete array;
}

TEST(Array2DViewTest, PlusTest) {
  Array array1 = {1, 2, 3, 4, 5, 6};
  Array array2 = {6, 7, 8, 9, 10, 11, 12};
  Array array3 = {1, 2, 3, 4, 5, 6};
  ArrayWithVectorsView<2> view1(array1, 0, 2u, 3u);
  ArrayWithVectorsView<2> view2(array2, 1, 2u, 3u);
  ArrayWithVectorsView<2> view3(array3, 0, 3u, 2u);

  auto [result, array] = view1 + view2;

  ASSERT_ANY_THROW(view2 + view3);
  ASSERT_EQ(result.Get(0u, 0u).ToUInt32(), view1.Get(0u, 0u).ToUInt32() + view2.Get(0u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 1u).ToUInt32(), view1.Get(0u, 1u).ToUInt32() + view2.Get(0u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 2u).ToUInt32(), view1.Get(0u, 2u).ToUInt32() + view2.Get(0u, 2u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 0u).ToUInt32(), view1.Get(1u, 0u).ToUInt32() + view2.Get(1u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 1u).ToUInt32(), view1.Get(1u, 1u).ToUInt32() + view2.Get(1u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 2u).ToUInt32(), view1.Get(1u, 2u).ToUInt32() + view2.Get(1u, 2u).ToUInt32());
  ASSERT_NE(&result.GetContainer(), &view1.GetContainer());
  ASSERT_NE(&result.GetContainer(), &view2.GetContainer());
  delete array;
}

TEST(Array2DViewTest, MinusTest) {
  Array array1 = {6, 7, 8, 9, 10, 11, 12};
  Array array2 = {1, 2, 3, 4, 5, 6};
  Array array3 = {1, 2, 3, 4, 5, 6};
  ArrayWithVectorsView<2> view1(array1, 1, 2u, 3u);
  ArrayWithVectorsView<2> view2(array2, 0, 2u, 3u);
  ArrayWithVectorsView<2> view3(array3, 0, 3u, 2u);

  auto [result, array] = view1 - view2;

  ASSERT_ANY_THROW(view2 - view3);
  ASSERT_EQ(result.Get(0u, 0u).ToUInt32(), view1.Get(0u, 0u).ToUInt32() - view2.Get(0u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 1u).ToUInt32(), view1.Get(0u, 1u).ToUInt32() - view2.Get(0u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 2u).ToUInt32(), view1.Get(0u, 2u).ToUInt32() - view2.Get(0u, 2u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 0u).ToUInt32(), view1.Get(1u, 0u).ToUInt32() - view2.Get(1u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 1u).ToUInt32(), view1.Get(1u, 1u).ToUInt32() - view2.Get(1u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 2u).ToUInt32(), view1.Get(1u, 2u).ToUInt32() - view2.Get(1u, 2u).ToUInt32());
  ASSERT_NE(&result.GetContainer(), &view1.GetContainer());
  ASSERT_NE(&result.GetContainer(), &view2.GetContainer());
  delete array;
}

TEST(Array2DViewTest, MakeArrayTest) {
  auto [view, array] = ArrayView<2>::MakeArray(2u, 2u);
  view[0][0] = 1u;
  view[0][1] = 2u;
  view[1][0] = 3u;
  view[1][1] = 4u;

  ASSERT_EQ(array->At(0).ToUInt32(), 1u);
  ASSERT_EQ(array->At(1).ToUInt32(), 2u);
  ASSERT_EQ(array->At(2).ToUInt32(), 3u);
  ASSERT_EQ(array->At(3).ToUInt32(), 4u);
  delete array;
}

TEST(Array2DViewTest, InputTest) {
  std::string input = "1 2 3 4 5";
  std::stringstream input_stream(input);
  Array array(5);
  ArrayWithVectorsView<2> view(array, 1, 2u, 2u);
  input_stream >> view;
  ASSERT_EQ(view.Get(0u, 0u).ToUInt32(), 1u);
  ASSERT_EQ(view.Get(0u, 1u).ToUInt32(), 2u);
  ASSERT_EQ(view.Get(1u, 0u).ToUInt32(), 3u);
  ASSERT_EQ(view.Get(1u, 1u).ToUInt32(), 4u);
}

TEST(Array2DViewTest, OutputTest) {
  std::stringstream output_stream;
  Array array = {1, 2, 3, 4, 5};
  ArrayWithVectorsView<2> view(array, 1, 2u, 2u);
  output_stream << view;
  ASSERT_EQ(output_stream.str(), "2 3 4 5");
}

TEST(Array3DViewTest, EmptyTest) {
  Array array = {1, 2, 3, 4, 5, 6, 7, 8};
  ArrayView<3> view(array, 0, 2u, 2u, 2u);
}

TEST(Array3DViewTest, WrongViewTest) {
  Array array = {1, 2, 3, 4, 5};

  ASSERT_ANY_THROW(ArrayView<3>(array, 0, 2u, 2u, 2u));
}

TEST(Array3DViewTest, AccesToElementsTest) {
  Array array = {1, 2, 3, 4, 5, 6, 7, 8};
  ArrayView<3> view(array, 0, 2u, 2u, 2u);

  view[0][1][1] = 20u;

  ASSERT_EQ(array[3].ToUInt32(), 20u);
  ASSERT_EQ(array[2].ToUInt32(), view[0][1][0].ToUInt32());
  ASSERT_ANY_THROW(view[2]);
  ASSERT_ANY_THROW(view[0][2]);
  ASSERT_ANY_THROW(view[0][0][2]);
}

TEST(Array3DViewTest, OffsetTest) {
  Array array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayView<3> view(array, 1, 2u, 2u, 2u);

  ASSERT_EQ(array[1].ToUInt32(), view[0][0][0].ToUInt32());
  ASSERT_ANY_THROW(view[4]);
}

TEST(Array3DViewTest, GetTest) {
  Array array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ArrayView<3> view(array, 1, 2u, 2u, 2u);

  view.Get(0u, 0u, 0u) = 20u;

  ASSERT_EQ(array[1].ToUInt32(), 20u);
  ASSERT_EQ(array[3].ToUInt32(), view.Get(0u, 1u, 0u).ToUInt32());
}

TEST(Array3DViewTest, GetDimensionTest) {
  Array array(24);
  ArrayView<3> view(array, 0, 2u, 3u, 4u);

  ASSERT_EQ(view.GetDimension(0), 2u);
  ASSERT_EQ(view.GetDimension(1), 3u);
  ASSERT_EQ(view.GetDimension(2), 4u);
}

TEST(Array3DViewTest, GetContainerTest) {
  Array array = {1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(&ArrayView<3>(array, 0, 2u, 2u, 2u).GetContainer(), &array);
}

TEST(Array3DViewTest, MultTest) {
  Array array1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ArrayWithVectorsView<3> view(array1, 0, 2u, 2u, 2u);
  uint32_t lambda = 2;
  auto [result, array] = view * lambda;
  ASSERT_EQ(result.Get(0u, 0u, 0u).ToUInt32(), view.Get(0u, 0u, 0u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(0u, 0u, 1u).ToUInt32(), view.Get(0u, 0u, 1u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(0u, 1u, 0u).ToUInt32(), view.Get(0u, 1u, 0u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(0u, 1u, 1u).ToUInt32(), view.Get(0u, 1u, 1u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(1u, 0u, 0u).ToUInt32(), view.Get(1u, 0u, 0u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(1u, 0u, 1u).ToUInt32(), view.Get(1u, 0u, 1u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(1u, 1u, 0u).ToUInt32(), view.Get(1u, 1u, 0u).ToUInt32() * lambda);
  ASSERT_EQ(result.Get(1u, 1u, 1u).ToUInt32(), view.Get(1u, 1u, 1u).ToUInt32() * lambda);
  ASSERT_NE(&result.GetContainer(), &view.GetContainer());
  delete array;
}

TEST(Array3DViewTest, PlusTest) {
  Array array1 = {1, 2, 3, 4, 5, 6, 7, 8};
  Array array2 = {6, 7, 8, 9, 10, 11, 12, 13, 14};
  Array array3(12);
  ArrayWithVectorsView<3> view1(array1, 0, 2u, 2u, 2u);
  ArrayWithVectorsView<3> view2(array2, 1, 2u, 2u, 2u);
  ArrayWithVectorsView<3> view3(array3, 0, 2u, 2u, 3u);

  auto [result, array] = view1 + view2;

  ASSERT_ANY_THROW(view2 + view3);
  ASSERT_EQ(result.Get(0u, 0u, 0u).ToUInt32(), view1.Get(0u, 0u, 0u).ToUInt32() + view2.Get(0u, 0u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 0u, 1u).ToUInt32(), view1.Get(0u, 0u, 1u).ToUInt32() + view2.Get(0u, 0u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 1u, 0u).ToUInt32(), view1.Get(0u, 1u, 0u).ToUInt32() + view2.Get(0u, 1u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 1u, 1u).ToUInt32(), view1.Get(0u, 1u, 1u).ToUInt32() + view2.Get(0u, 1u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 0u, 0u).ToUInt32(), view1.Get(1u, 0u, 0u).ToUInt32() + view2.Get(1u, 0u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 0u, 1u).ToUInt32(), view1.Get(1u, 0u, 1u).ToUInt32() + view2.Get(1u, 0u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 1u, 0u).ToUInt32(), view1.Get(1u, 1u, 0u).ToUInt32() + view2.Get(1u, 1u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 1u, 1u).ToUInt32(), view1.Get(1u, 1u, 1u).ToUInt32() + view2.Get(1u, 1u, 1u).ToUInt32());
  ASSERT_NE(&result.GetContainer(), &view1.GetContainer());
  ASSERT_NE(&result.GetContainer(), &view2.GetContainer());
  delete array;
}

TEST(Array3DViewTest, MinusTest) {
  Array array1 = {6, 7, 8, 9, 10, 11, 12, 13, 14};
  Array array2 = {1, 2, 3, 4, 5, 6, 7, 8};
  Array array3(12);
  ArrayWithVectorsView<3> view1(array1, 1, 2u, 2u, 2u);
  ArrayWithVectorsView<3> view2(array2, 0, 2u, 2u, 2u);
  ArrayWithVectorsView<3> view3(array3, 0, 2u, 2u, 3u);

  auto [result, array] = view1 - view2;

  ASSERT_ANY_THROW(view2 - view3);
  ASSERT_EQ(result.Get(0u, 0u, 0u).ToUInt32(), view1.Get(0u, 0u, 0u).ToUInt32() - view2.Get(0u, 0u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 0u, 1u).ToUInt32(), view1.Get(0u, 0u, 1u).ToUInt32() - view2.Get(0u, 0u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 1u, 0u).ToUInt32(), view1.Get(0u, 1u, 0u).ToUInt32() - view2.Get(0u, 1u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(0u, 1u, 1u).ToUInt32(), view1.Get(0u, 1u, 1u).ToUInt32() - view2.Get(0u, 1u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 0u, 0u).ToUInt32(), view1.Get(1u, 0u, 0u).ToUInt32() - view2.Get(1u, 0u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 0u, 1u).ToUInt32(), view1.Get(1u, 0u, 1u).ToUInt32() - view2.Get(1u, 0u, 1u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 1u, 0u).ToUInt32(), view1.Get(1u, 1u, 0u).ToUInt32() - view2.Get(1u, 1u, 0u).ToUInt32());
  ASSERT_EQ(result.Get(1u, 1u, 1u).ToUInt32(), view1.Get(1u, 1u, 1u).ToUInt32() - view2.Get(1u, 1u, 1u).ToUInt32());
  ASSERT_NE(&result.GetContainer(), &view1.GetContainer());
  ASSERT_NE(&result.GetContainer(), &view2.GetContainer());
  delete array;
}

TEST(Array3DViewTest, MakeArrayTest) {
  auto [view, array] = ArrayView<3>::MakeArray(2u, 2u, 2u);
  view[0][0][0] = 1u;
  view[0][0][1] = 2u;
  view[0][1][0] = 3u;
  view[0][1][1] = 4u;
  view[1][0][0] = 5u;
  view[1][0][1] = 6u;
  view[1][1][0] = 7u;
  view[1][1][1] = 8u;

  ASSERT_EQ(array->At(0).ToUInt32(), 1u);
  ASSERT_EQ(array->At(1).ToUInt32(), 2u);
  ASSERT_EQ(array->At(2).ToUInt32(), 3u);
  ASSERT_EQ(array->At(3).ToUInt32(), 4u);
  ASSERT_EQ(array->At(4).ToUInt32(), 5u);
  ASSERT_EQ(array->At(5).ToUInt32(), 6u);
  ASSERT_EQ(array->At(6).ToUInt32(), 7u);
  ASSERT_EQ(array->At(7).ToUInt32(), 8u);
  delete array;
}

TEST(Array3DViewTest, InputTest) {
  std::string input = "1 2 3 4 5 6 7 8";
  std::stringstream input_stream(input);
  auto [view, array] = ArrayWithVectorsView<3>::MakeArray(2u, 2u, 2u);
  input_stream >> view;
  ASSERT_EQ(view[0][0][0].ToUInt32(), 1u);
  ASSERT_EQ(view[0][0][1].ToUInt32(), 2u);
  ASSERT_EQ(view[0][1][0].ToUInt32(), 3u);
  ASSERT_EQ(view[0][1][1].ToUInt32(), 4u);
  ASSERT_EQ(view[1][0][0].ToUInt32(), 5u);
  ASSERT_EQ(view[1][0][1].ToUInt32(), 6u);
  ASSERT_EQ(view[1][1][0].ToUInt32(), 7u);
  ASSERT_EQ(view[1][1][1].ToUInt32(), 8u);
  delete array;
}

TEST(Array3DViewTest, OutputTest) {
  std::stringstream output_stream;
  Array array = {1, 2, 3, 4, 5, 6, 7, 8};
  ArrayWithVectorsView<3> view(array, 0, 2u, 2u, 2u);
  output_stream << view;
  ASSERT_EQ(output_stream.str(), "1 2 3 4 5 6 7 8");
}