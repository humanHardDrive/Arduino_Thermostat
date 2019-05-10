#include "TempSensor.h"

TempSensor::TempSensor()
{
  seedRnd(analogRead(0));
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

void TempSensor::pair(uint16_t timeout)
{
  m_pRadio->stopListening();
  m_pRadio->openWritingPipe(DISCOVERY_PIPE);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, DISCOVERY_PIPE);
  m_pRadio->startListening();

  RemoteSensor::pair(timeout);
}

uint16_t TempSensor::rnd()
{
  return (uint16_t)random(0, 0xFFFF);
}

void TempSensor::seedRnd(uint16_t seed)
{
  randomSeed(seed);
}

uint32_t TempSensor::clockms()
{
  return millis();
}

int TempSensor::write(const void* buffer, uint16_t len)
{
  uint16_t i = 0;

  m_pRadio->stopListening();

  while (i < len)
  {
    uint8_t size = 0;
    if (len > MAX_PAYLOAD_SIZE)
      size = MAX_PAYLOAD_SIZE;
    else
      size = len;

    m_pRadio->write(buffer + i, size);
    i += size;
  }

  m_pRadio->startListening();

#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
  Serial.print(F("SENT: "));
  printArr(buffer, (uint8_t)len);
  Serial.println();
#endif

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

void TempSensor::print(const char* str)
{
#ifdef SERIAL_DEBUG
  Serial.println(str);
#endif
}

void TempSensor::print(int32_t num)
{
#ifdef SERIAL_DEBUG
  Serial.println(num);
#endif
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

