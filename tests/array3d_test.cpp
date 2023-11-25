#include <lib/array.h>
#include <lib/uint17_view.h>
#include <lib/array_view.h>
#include <gtest/gtest.h>
#include <stdexcept>

using namespace uint17;

TEST(ArrayTest, EmptyTest) {
  Array array(5);
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

TEST(ArrayTest, LengthTest) {
  size_t length = 5;
  const Array array(length);

  ASSERT_EQ(array.GetLength(), length);
}

TEST(ArrayTest, CopyTest) {
  Array array1(3);

  array1[0] = 15u;
  
  Array array2 = array1;

  array2[0] = 16u;
  
  Array array3(array1);

  array3[0] = 17u;

  ASSERT_EQ(array1[0].ToUInt32(), 15u);
  ASSERT_EQ(array2[0].ToUInt32(), 16u);
  ASSERT_EQ(array3[0].ToUInt32(), 17u);
}

TEST(ArrayTest, InitalizerListTest) {
  uint32_t val1 = 10;
  uint32_t val2 = 10000;
  uint32_t val3 = 66000;
  uint32_t val4 = 2;
  
  const Array array = {val1, val2, val3, val4};

  ASSERT_EQ(array.GetLength(), 4);
  ASSERT_EQ(array[0].ToUInt32(), val1);
  ASSERT_EQ(array[1].ToUInt32(), val2);
  ASSERT_EQ(array[2].ToUInt32(), val3);
  ASSERT_EQ(array[3].ToUInt32(), val4);
}

TEST(ArrayTest, AtTest) {
  Array array = {1u, 2u, 3u, 4u};

  ASSERT_EQ(array.At(1).ToUInt32(), 2u);
  ASSERT_THROW(array.At(4), std::out_of_range);
}

TEST(UInt17ViewTest, FromUInt16Test) {
  uint16_t val = 32;
  Array array(1);

  array[0] = val;

  ASSERT_EQ(array[0].ToUInt32(), val);
}

TEST(UInt17ViewTest, FromUInt32Test) {
  uint32_t val = 65000;
  Array array(1);

  array[0] = val;

  ASSERT_EQ(array[0].ToUInt32(), val);
}

TEST(UInt17ViewTest, SetToZeroTest) {
  uint32_t val = 65000;
  Array array(1);

  array[0] = val;

  array[0].SetToZero();

  ASSERT_EQ(array[0].ToUInt32(), 0);
}

TEST(UInt17ViewTest, PlusTest) {
  uint32_t val1 = 20;
  uint32_t val2 = 15;
  uint32_t val3 = 50;
  uint32_t val4 = 10;

  Array array(3);

  array[0] = val1;
  array[1] = val2;
  array[2] = val3;

  array[0] += array[1];
  array[2] += val4;

  ASSERT_EQ(array[0].ToUInt32(), val1 + val2);
  ASSERT_EQ(array[2].ToUInt32(), val3 + val4);
}

TEST(UInt17ViewTest, MinusTest) {
  uint32_t val1 = 20;
  uint32_t val2 = 15;
  uint32_t val3 = 50;
  uint32_t val4 = 10;

  Array array(3);

  array[0] = val1;
  array[1] = val2;
  array[2] = val3;

  array[0] -= array[1];
  array[2] -= val4;

  ASSERT_EQ(array[0].ToUInt32(), val1 - val2);
  ASSERT_EQ(array[2].ToUInt32(), val3 - val4);
}

TEST(UInt17ViewTest, MultTest) {
  uint32_t val1 = 20;
  uint32_t val2 = 15;
  uint32_t val3 = 50;
  uint32_t val4 = 10;

  Array array(3);

  array[0] = val1;
  array[1] = val2;
  array[2] = val3;

  array[0] *= array[1];
  array[2] *= val4;

  ASSERT_EQ(array[0].ToUInt32(), val1 * val2);
  ASSERT_EQ(array[2].ToUInt32(), val3 * val4);
}


TEST(ArrayViewTest, EmptyTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView view(array);
}

TEST(ArrayViewTest, ChangeValuesTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView view(array);
  view[0] = 2u;
  ASSERT_EQ(array[0].ToUInt32(), 2u);
}

TEST(ArrayViewTest, PartialViewTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView view(array, 1, 4);
  view[0] = 2u;
  ASSERT_EQ(array[1].ToUInt32(), 2u);
}

TEST(ArrayViewTest, WrongArrayViewCreated) {
  Array array = {1, 2, 3, 4, 5};
  ASSERT_ANY_THROW(ArrayView(array, 3, 1));
  ASSERT_ANY_THROW(ArrayView(array, 6, 7));
}

TEST(ArrayViewTest, AtTest) {
  Array array = {1, 2, 3, 4, 5};
  ArrayView view1(array, 2, 5);
  ArrayView view2(array);

  ASSERT_EQ(view1.At(0).ToUInt32(), view2.At(2).ToUInt32());
  ASSERT_THROW(view1.At(4), std::out_of_range);
}
