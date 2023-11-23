#pragma once

#include <cstdint>

class UInt17View {
 public:
  UInt17View(uint8_t* data, uint8_t offset);
  UInt17View& operator=(uint16_t number);
  UInt17View& operator=(uint32_t number);
  UInt17View& operator+=(const UInt17View& other);
  UInt17View& operator+=(uint32_t other);
  UInt17View& operator-=(const UInt17View& other);
  UInt17View& operator-=(uint32_t other);
  UInt17View& operator*=(const UInt17View& other);
  UInt17View& operator*=(uint32_t other);
  [[nodiscard]] uint32_t ToUInt32() const;
 private:
  uint8_t* data_;
  uint8_t offset_;
};
