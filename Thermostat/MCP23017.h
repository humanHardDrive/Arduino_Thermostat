#ifndef __MCP_23s17_H__
#define __MCP_23s17_H__

#include <Arduino.h>

class MCP23s17
{
  public:  
  MCP23s17(byte csPin, byte address);
  MCP23s17(byte csPin, byte rstPin, byte address);
  ~MCP23s17();

  void reset();

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
  byte m_CSPin, m_RstPin, m_devAddress;
  byte m_Bank;
};

#endif
