#include "FM25V10.h"

#include <SPI.h>

FM25V10::FM25V10(byte csPin) :
  m_CSPin(csPin)
{
  pinMode(m_CSPin, OUTPUT);
  digitalWrite(m_CSPin, HIGH);
}

FM25V10::~FM25V10()
{
}

byte FM25V10::read(uint32_t address)
{
  address &= ADDRESS_MASK;
  byte retVal = 0xFF;

  digitalWrite(m_CSPin, LOW);

  SPI.transfer(READ_OP_CODE);
  SPI.transfer(((byte*)&address)[2]);
  SPI.transfer(((byte*)&address)[1]);
  SPI.transfer(((byte*)&address)[0]);
  retVal = SPI.transfer(0x00);

  digitalWrite(m_CSPin, HIGH);

  return retVal;
}

byte FM25V10::read(uint32_t address, byte* buffer, uint32_t len)
{
  address &= ADDRESS_MASK;

  digitalWrite(m_CSPin, LOW);

  SPI.transfer(READ_OP_CODE);
  SPI.transfer(((byte*)&address)[2]);
  SPI.transfer(((byte*)&address)[1]);
  SPI.transfer(((byte*)&address)[0]);

  for (uint32_t i = 0; i < len; i++)
    buffer[i] = SPI.transfer(0x00);

  digitalWrite(m_CSPin, HIGH);
}


void FM25V10::write(uint32_t address, byte val)
{
  address &= ADDRESS_MASK;

  writeEnable();

  digitalWrite(m_CSPin, LOW);

  SPI.transfer(WRITE_OP_CODE);
  SPI.transfer(((byte*)&address)[2]);
  SPI.transfer(((byte*)&address)[1]);
  SPI.transfer(((byte*)&address)[0]);
  SPI.transfer(val);

  digitalWrite(m_CSPin, HIGH);
}

void FM25V10::write(uint32_t address, byte* buffer, uint32_t len)
{
  address &= ADDRESS_MASK;

  writeEnable();

  digitalWrite(m_CSPin, LOW);

  SPI.transfer(WRITE_OP_CODE);
  SPI.transfer(((byte*)&address)[2]);
  SPI.transfer(((byte*)&address)[1]);
  SPI.transfer(((byte*)&address)[0]);

  for(uint32_t i = 0; i < len; i++)
    SPI.transfer(buffer[i]);

  digitalWrite(m_CSPin, HIGH);
}


void FM25V10::writeEnable()
{
  digitalWrite(m_CSPin, LOW);
  SPI.transfer(WRITE_ENABLE_OP_CODE);
  digitalWrite(m_CSPin, HIGH);
}

