#include "ThermostatStation.h"

ThermoStation::ThermoStation() :
  m_HeatMode(0),
  m_FanMode(0),
  m_HeatOn(false),
  m_CoolOn(false),
  m_pRadio(NULL)
{
  m_SavedData.txPipe = 0xAAAAAAAAAA;
  m_SavedData.rxPipe = 0xAAAAAAAAAB;
}

ThermoStation::~ThermoStation()
{
}

void ThermoStation::addRadio(RF24* pRadio)
{
  m_pRadio = pRadio;
}

void ThermoStation::begin()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif
  
  m_pRadio->begin();
  m_pRadio->setAutoAck(1);
  m_pRadio->setRetries(0, 15);
  m_pRadio->enableDynamicPayloads();

  m_pRadio->openWritingPipe(m_SavedData.txPipe);
  m_pRadio->openReadingPipe(1, m_SavedData.rxPipe);
  
  m_pRadio->startListening();
}

void ThermoStation::setHeatMode(byte mode)
{
  if (mode < ALL_HEAT_MODES)
    m_HeatMode = mode;
}

void ThermoStation::setFanMode(byte mode)
{
  if (mode < ALL_FAN_MODES)
    m_FanMode = mode;
}

void ThermoStation::setTargetTemp(byte temp)
{
  m_TargetTemp = temp;
}

byte ThermoStation::getTargetTemp()
{
  return m_TargetTemp;
}

bool ThermoStation::isFanOn()
{
  return (m_FanMode == ON || m_HeatOn || m_CoolOn);
}

bool ThermoStation::isHeatOn()
{
  return m_HeatOn;
}

bool ThermoStation::isCoolOn()
{
  return m_CoolOn;
}

void ThermoStation::startDiscovery(uint32_t timeout)
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif
  
  m_pRadio->openWritingPipe(discoveryPipe[0]);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, discoveryPipe[1]);
  m_pRadio->stopListening();

  BaseStation::startDiscovery(timeout);
}

void ThermoStation::stopDiscovery()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif
  
  m_pRadio->openWritingPipe(m_SavedData.txPipe);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, m_SavedData.rxPipe);
  m_pRadio->startListening();
}

void ThermoStation::background(DateTime t)
{
  BaseStation::background();

  byte day = dayofweek(t);
  byte isWeekend = 0;

  if (day == SATURDAY || day == SUNDAY)
    isWeekend = 1;

  for (byte i = 0; i < NUM_TIME_DIV; i++)
  {
    TEMP_RULE rule = m_TempRules[isWeekend][m_HeatMode][i];

    if (t.hour() > rule.h || t.minute() > rule.m)
      m_TargetTemp = rule.temp;
  }
}

uint8_t ThermoStation::dayofweek(DateTime date)
{
  static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  uint16_t y, m, d;

  y = date.year();
  m = date.month();
  d = date.day();

  y -= m < 3;
  return ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

int ThermoStation::write(const void* buf, uint16_t len)
{
  m_pRadio->stopListening();

  while (len > 0)
  {
    uint8_t size = 0;
    if (len > MAX_PAYLOAD_SIZE)
      size = MAX_PAYLOAD_SIZE;
    else
      size = len;

    m_pRadio->write(buf, size);
    len -= size;
  }

  m_pRadio->startListening();

  return 0;
}

int ThermoStation::available()
{
  return 0;
}

int ThermoStation::read(const void* buf, uint16_t len)
{
  return 0;
}

void ThermoStation::save(uint16_t addr, const void* buf, uint16_t len)
{
}

void ThermoStation::load(uint16_t addr, const void* buf, uint16_t len)
{

}

uint32_t ThermoStation::clockms()
{
  return millis();
}

void ThermoStation::print(const char* str)
{
  Serial.println(str);
}

void ThermoStation::print(int32_t num)
{
  Serial.println(num);
}

