#ifndef __MCP_23s17_H__
#define __MCP_23s17_H__

#include <Arduino.h>

class MCP23s17
{
  public:  
  MCP23s17(byte csPin, byte address);
  ~MCP23s17();

  void writeReg(byte reg, byte val);
  byte readReg(byte reg);

  enum REGISTER
  {
    IODIRA = 0,
    IODIRB,
    IPOLA,
    IPOLB,
    GPINTENA,
    GPINTENB,
    DEFVALA,
    DEFVALB,
    INTCONA,
    INTCONB,
    IOCON,
    IOCON_MIRROR,
    GPPUA,
    GPPUB,
    INTFA,
    INTFB,
    INTCAPA,
    INTCAPB,
    GPIOA,
    GPIOB,
    OLATA,
    OLATB,
    TOTAL_REGISTERS
  };

  private:
  byte m_CSPin, m_devAddress;
  byte m_Bank;

  const byte REG_ADDRESS[2][TOTAL_REGISTERS] = 
  {
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
     0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15}, 
    {0x00, 0x10, 0x01, 0x11, 0x02, 0x12, 0x03, 0x13, 0x04, 0x14, 0x05,
     0x15, 0x06, 0x16, 0x07, 0x17, 0x08, 0x18, 0x09, 0x19, 0x0A, 0x1A}
   };
};

#endif
