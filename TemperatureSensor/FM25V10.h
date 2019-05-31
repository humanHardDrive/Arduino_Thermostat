#ifndef __FM25V10_H__
#define __FM25V10_H__

#include <Arduino.h>

class FM25V10
{
  public:
  FM25V10(byte csPin);
  ~FM25V10();

  byte read(uint32_t address);
  byte read(uint32_t address, byte* buffer, uint32_t len);

  void write(uint32_t address, byte val);
  void write(uint32_t address, byte* buffer, uint32_t len);

  private:
  void writeEnable();

  private:
  const byte WRITE_ENABLE_OP_CODE = 0b00000110;
  const byte WRITE_DISABLE_OP_CODE = 0b00000100;
  const byte WRITE_OP_CODE = 0b00000010;
  const byte READ_OP_CODE = 0b00000011;
  const uint32_t ADDRESS_MASK = 0x1FFFF;

  byte m_CSPin;
};

#endif
