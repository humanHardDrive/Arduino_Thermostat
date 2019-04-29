#include "TempSensor.h"

TempSensor::TempSensor(RF24* pRadio) :
  m_pRadio(pRadio)
{

}

TempSensor::~TempSensor()
{

}

uint32_t TempSensor::clockms()
{
  return millis();
}

void TempSensor::print(const char* str)
{
  Serial.print(str);
}

int TempSensor::write(const void* buffer, uint16_t len)
{
  return 0;
}

int TempSensor::available()
{
  return 0;
}

int TempSensor::read(const void* buffer, uint16_t len)
{
  return 0;
}

void TempSensor::save(uint16_t addr, const void* buffer, uint16_t len)
{

}

void TempSensor::load(uint16_t addr, const void* buffer, uint16_t len)
{

}

