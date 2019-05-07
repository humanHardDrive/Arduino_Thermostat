#include "TempSensor.h"

TempSensor::TempSensor()
{

}

TempSensor::~TempSensor()
{

}

void TempSensor::addRadio(RF24* pRadio)
{
  m_pRadio = pRadio;
}

void TempSensor::begin()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  m_pRadio->begin();
  m_pRadio->enableDynamicPayloads();
  m_pRadio->startListening();
}

void TempSensor::pair()
{
  m_pRadio->stopListening();
  m_pRadio->openWritingPipe(DISCOVERY_PIPE);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, DISCOVERY_PIPE);
  m_pRadio->startListening();

  RemoteSensor::pair();
}

uint32_t TempSensor::clockms()
{
  return millis();
}

void TempSensor::print(const char* str)
{
  Serial.println(str);
}

int TempSensor::write(const void* buffer, uint16_t len)
{
  return 0;
}

int TempSensor::available()
{
  return m_pRadio->available();
}

int TempSensor::read(const void* buffer, uint16_t len)
{
  if (available())
  {
    uint16_t size = m_pRadio->getDynamicPayloadSize();
    m_pRadio->read(buffer, size);

#ifdef SERIAL_DEBUG
    Serial.println(__PRETTY_FUNCTION__);
    Serial.print("RECV: ");
    printArr(buffer, (uint8_t)size);
    Serial.println();
#endif

    return size;
  }

  return 0;
}

void TempSensor::save(uint16_t addr, const void* buffer, uint16_t len)
{

}

void TempSensor::load(uint16_t addr, const void* buffer, uint16_t len)
{

}

void TempSensor::printArr(void* buf, uint8_t len)
{
  for (uint8_t i = 0; i < len; i++)
  {
    byte b = ((byte*)buf)[i];

    Serial.print("0x");
    if (b <= 0x0F)
      Serial.print('0');

    Serial.print(b, HEX);
    Serial.print(' ');
  }
  Serial.println();
}

