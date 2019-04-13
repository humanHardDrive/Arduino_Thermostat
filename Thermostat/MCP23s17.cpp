#include "MCP23s17.h"

#include <SPI.h>

MCP23s17::MCP23s17(byte csPin, byte address) :
  m_CSPin(csPin),
  m_RstPin(0xFF),
  m_devAddress(address & 0x03),
  m_Bank(0)
{
  pinMode(m_CSPin, OUTPUT);
  
  digitalWrite(m_CSPin, HIGH);
}

MCP23s17::MCP23s17(byte csPin, byte rstPin, byte address) :
  m_CSPin(csPin),
  m_RstPin(rstPin),
  m_devAddress(address),
  m_Bank(0)
{
  pinMode(m_CSPin, OUTPUT);
  pinMode(m_RstPin, OUTPUT);

  digitalWrite(m_CSPin, HIGH);
  digitalWrite(m_RstPin, HIGH);
}

MCP23s17::~MCP23s17()
{
}

void MCP23s17::reset()
{
  if(m_RstPin != 0xFF)
  {
    digitalWrite(m_RstPin, LOW);
    delayMicroseconds(500);
    digitalWrite(m_RstPin, HIGH);
  }
}

void MCP23s17::writeReg(byte reg, byte val)
{
  if (reg < TOTAL_REGISTERS)
  {
    digitalWrite(m_CSPin, LOW);

    SPI.transfer(0x40 | (m_devAddress << 1) | 0x00);
    SPI.transfer(REG_ADDRESS[m_Bank][reg]);
    SPI.transfer(val);
    
    digitalWrite(m_CSPin, HIGH);
  }
}

byte MCP23s17::readReg(byte reg)
{
  byte retVal = 0;
  
  if (reg < TOTAL_REGISTERS)
  {
    digitalWrite(m_CSPin, LOW);

    SPI.transfer(0x40 | (m_devAddress << 1) | 0x01);
    SPI.transfer(REG_ADDRESS[m_Bank][reg]);
    retVal = SPI.transfer(0x00);
    
    digitalWrite(m_CSPin, HIGH);
  }

  return retVal;
}

