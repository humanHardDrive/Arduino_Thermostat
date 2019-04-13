#include "MCP23s17.h"

#include <SPI.h>

MCP23s17::MCP23s17(byte csPin, byte address) :
  m_CSPin(csPin),
  m_devAddress(address),
  m_Bank(0)
{
  pinMode(m_CSPin, INPUT);
}

MCP23s17::~MCP23s17()
{ 
}

void MCP23s17::writeReg(byte reg, byte val)
{
  if(reg < TOTAL_REGISTERS)
  {
  }
}

byte MCP23s17::readReg(byte reg)
{
  if(reg < TOTAL_REGISTERS)
  {
  }
  
  return 0;
}

