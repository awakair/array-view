#include "uint17_view.h"

namespace uint17 {

namespace bitwise_actions {
const uint8_t kResetFirstByte[] = {0b00000000, 0b10000000, 0b11000000, 0b11100000,
                                   0b11110000, 0b11111000, 0b11111100, 0b11111110};
const uint8_t kResetLastByte[] = {0b0111111, 0b00111111, 0b00011111, 0b00001111,
                                  0b00000111, 0b00000011, 0b00000001, 0b00000000};
const uint8_t kGetFirstByte[] = {0b11111111, 0b01111111, 0b00111111, 0b00011111,
                                 0b00001111, 0b00000111, 0b00000011, 0b00000001};
const uint8_t kGetLastByte[] = {0b10000000, 0b11000000, 0b11100000, 0b11110000,
                                0b11111000, 0b11111100, 0b11111110, 0b11111111};
}

UInt17View::UInt17View(uint8_t* data, const uint8_t offset)
  : data_(data), start_(offset), end_(kBitLength - (8 - start_ + 8) - 1) {}

UInt17View& UInt17View::SetToZero() {
  data_[0] &= bitwise_actions::kResetFirstByte[start_];
  data_[1] = 0;
  data_[2] &= bitwise_actions::kResetLastByte[end_];

  return *this;
}

UInt17View& UInt17View::operator=(const uint32_t number) {
  this->SetToZero();
  /*
    After setting to zero number is stored as
    [1 1 1 1 0 0 0 0] [0 0 0 0 0 0 0 0] [0 0 0 0 0 1 1 1]
             |                                   |
	     start_                              end_
    Overflow ignored
    I need to get first 15+n-th bits of uint32_t number to store if first byte of UInt17View number
    n = 8 - start_ (8 - 4 = 4 in example above)
    I need to shift my number for 17 - n bits and cast it to uint8_t to execute bitwise or with first byte of number
   */
  const auto n = 8 - start_;
  const auto shift_first_part = 17 - n;
  data_[0] |= static_cast<uint8_t>(number >> shift_first_part);
  /*
    Then I just set second byte to next 8 bits of my number
    To do it I can just shift my number to remove it's last bits
   */
  const auto shift_second_part = kBitLength - n - 8;
  data_[1] = static_cast<uint8_t>(number >> shift_second_part);
  /*
    Finally I can just shift my number to the right to execute bitwise or with third byte
   */
  const auto left_bits = kBitLength - n - 8;
  const auto shift_third_part = 8 - left_bits;
  data_[2] |= static_cast<uint8_t>(number) << shift_third_part;

  return *this;
}

UInt17View& UInt17View::operator=(const uint16_t number) {
  return this->operator=(static_cast<uint32_t>(number));
}
UInt17View& UInt17View::operator=(const UInt17View& other) {
  return this->operator=(other.ToUInt32());
}


uint32_t UInt17View::ToUInt32() const {  // much simpler than operator=, see it first
  const auto shift_first_part = 8 + end_ + 1;
  const auto first_part = static_cast<uint32_t>(data_[0] & bitwise_actions::kGetFirstByte[start_]) << shift_first_part;
  const auto shift_second_part = end_ + 1;
  const auto second_part = static_cast<uint32_t>(data_[1]) << shift_second_part;
  const auto shift_third_part = 8 - end_ - 1;
  const auto third_part = static_cast<uint32_t>(data_[2] & bitwise_actions::kGetLastByte[end_]) >> shift_third_part;
  return first_part | second_part | third_part;
}

UInt17View& UInt17View::operator+=(const UInt17View& other) {
  return (*this += other.ToUInt32());
}
UInt17View& UInt17View::operator+=(const uint32_t other) {
  return (*this = this->ToUInt32() + other);
}
UInt17View& UInt17View::operator-=(const UInt17View& other) {
  return (*this -= other.ToUInt32());
}
UInt17View& UInt17View::operator-=(const uint32_t other) {
  return (*this = this->ToUInt32() - other);
}
UInt17View& UInt17View::operator*=(const UInt17View& other) {
  return (*this *= other.ToUInt32());
}
UInt17View& UInt17View::operator*=(const uint32_t other) {
  return (*this = this->ToUInt32() * other);
}

}  // namespace uint17

std::ostream& operator<<(std::ostream& stream, const uint17::UInt17View& value) {
  stream << value.ToUInt32();

  return stream;
}
std::istream& operator>>(std::istream& stream, uint17::UInt17View& value) {
  uint32_t number;
  stream >> number;
  value = number;

  return stream;
}
std::istream& operator>>(std::istream& stream, uint17::UInt17View&& value) {
  uint32_t number;
  stream >> number;
  value = number;

  return stream;
}
