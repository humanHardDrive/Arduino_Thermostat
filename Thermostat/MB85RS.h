#ifndef __MB85RS_H__
#define __MB85RS_H__

#include <Arduino.h>

class MB85RS
{
  public:
  MB85RS(byte csPin);
  ~MB85RS();

  void write(uint32_t addr, uint8_t val);
  void write(uint32_t addr, const uint8_t* buf, uint16_t len);

  uint8_t read(uint32_t addr);
  void read(uint32_t addr, uint8_t* buf, uint16_t len);

  private:
  byte m_CSPin;
};

#endif
