#include <iostream>
#include <cstdint>
#include <lib/uint17_view.h>
#include <lib/array.h>
#include <lib/array_view.h>

 using namespace uint17;

 template <typename T>
 void foo(T) = delete; 

int main() {
  Array some(5);
  uint32_t some_val = 20;
//  std::cin >> some_val;
//  std::cout << some_val << std::endl;
  some[0] = some_val;
  some[1] = ++some_val;
  some[2] = ++some_val;
  some[3] = ++some_val;
  some[4] = ++some_val;
//  ArrayView<1> view(some, 1, 4);

  size_t width = 2;
  size_t height = 2;
  ArrayView<2> view2d(some, 1, width, height);
  view2d[0][0] = 5u;
  view2d[0][1] = 6u;
  view2d[0].Get(0) = 9u;
  view2d[1][0] = 7u;
  view2d[1][1] = 8u;
  view2d.Get(--width, --height) = 10u;


  for (size_t i = 0; i != 5; ++i) {
    std::cout << some[i] << " ";
  }
  return EXIT_SUCCESS;
}
