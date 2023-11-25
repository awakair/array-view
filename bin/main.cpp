#include <iostream>
#include <cstdint>
#include <lib/uint17_view.h>
#include <lib/array.h>

 using namespace uint17;

int main() {
  Array some(5);
  uint16_t some_val;
  std::cin >> some_val;
  std::cout << some_val << std::endl;
  some[0] = some_val;
  some[1] = ++some_val;
  some[2] = ++some_val;
  std::cout << some[0] << " " << some[1] << " " << some[2];
  
  return EXIT_SUCCESS;
}
