#pragma once

#include <cstdint>
#include <iostream>

namespace uint17 {

class UInt17View {
 public:
  UInt17View(uint8_t* data, uint8_t offset);
  UInt17View& SetToZero();
  UInt17View& operator=(uint16_t number);
  UInt17View& operator=(uint32_t number);
  [[nodiscard]] uint32_t ToUInt32() const;
  UInt17View& operator+=(const UInt17View& other);
  UInt17View& operator+=(uint32_t other);
  UInt17View& operator-=(const UInt17View& other);
  UInt17View& operator-=(uint32_t other);
  UInt17View& operator*=(const UInt17View& other);
  UInt17View& operator*=(uint32_t other);
 private:
  uint8_t* data_;  // pointer to first byte of number (it's 3 bytes long)
  uint8_t start_;  // number of bit in first byte of number (from 0 to 7)
  uint8_t end_;  // number of bit in last byte of number (from 0 to 7)
  // [start_, end_]
};

}  // namespace uint17

std::ostream &operator<<(std::ostream &stream, const uint17::UInt17View &value);
std::istream &operator>>(std::istream &stream, uint17::UInt17View &value);