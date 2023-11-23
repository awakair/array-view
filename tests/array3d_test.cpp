#include <lib/ArgParser.h>
#include <gtest/gtest.h>

using namespace UInt17;

TEST(ArgParserTestSuite, EmptyTest) {
  Array3D array(3, 3, 3);

  array[1][1][1] = 5;

  ASSERT_EQ(array[1][1][1], 5);
}