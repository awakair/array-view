#include "UInt17View.h"

namespace BitwiseSetters {
  uint8_t zero[] = {0b01111111, }; 
}

UInt17View::UInt17View(uint8_t *data, uint8_t offset)
    : data_(data), offset_(offset) {}

UInt17View &UInt17View::operator=(uint16_t number) { return *this; }

UInt17View& UInt17View::operator=(uint32_t number) {
  return *this;
}

UInt17View& UInt17View::operator+=(const UInt17View& other) {
  return (*this += other.ToUInt32());
}
UInt17View& UInt17View::operator+=(uint32_t other) {
  return (*this = this->ToUInt32() + other);
}
UInt17View& UInt17View::operator-=(const UInt17View& other) {
  return (*this -= other.ToUInt32());
}
UInt17View& UInt17View::operator-=(uint32_t other) {
  return (*this = this->ToUInt32() - other);
}
UInt17View& UInt17View::operator*=(const UInt17View& other) {
  return (*this *= other.ToUInt32());
}
UInt17View& UInt17View::operator*=(uint32_t other) {
  return (*this = this->ToUInt32() * other);
}

uint32_t UInt17View::ToUInt32() const {
  return 0;
}
