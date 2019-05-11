#include "ThermostatStation.h"

ThermoStation::ThermoStation() :
  m_HeatMode(0),
  m_FanMode(0),
  m_HeatOn(false),
  m_CoolOn(false),
  m_pRadio(NULL)
{
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
  m_pRadio->enableDynamicPayloads();

  m_pRadio->openWritingPipe(m_SavedData.networkID);
  m_pRadio->openReadingPipe(1, m_SavedData.networkID);

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

  m_pRadio->openWritingPipe(DISCOVERY_PIPE);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, DISCOVERY_PIPE);
  m_pRadio->stopListening();

  BaseStation::startDiscovery(timeout);
}

void ThermoStation::stopDiscovery()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  m_pRadio->openWritingPipe(0xaaaaaaaaaa);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, 0xaaaaaaaaab);
  m_pRadio->startListening();

#ifdef SERIAL_DEBUG
  for (uint8_t i = 0; i < MAX_DISCOVERY; i++)
  {
    if (m_DiscoveredDevice[i].UID)
    {
      Serial.print(i);
      Serial.print(" ");
      Serial.print(F("Discovered 0x"));
      Serial.print(m_DiscoveredDevice[i].UID, HEX);
      Serial.print(" ");
      Serial.println(m_DiscoveredDevice[i].name);
    }
  }
#endif
}

void ThermoStation::getDiscoveredDevice(uint8_t index, uint32_t* UID, char* name)
{
  if (index < MAX_DISCOVERY)
  {
    if (UID)
      *UID = m_DiscoveredDevice[index].UID;

    if (name)
      name = m_DiscoveredDevice[index].name;
  }
}

bool ThermoStation::pair(uint32_t UID, uint32_t timeout)
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif
  
  bool bRetVal = false;

  m_pRadio->openWritingPipe(DISCOVERY_PIPE);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, DISCOVERY_PIPE);
  m_pRadio->stopListening();
  
  bRetVal = BaseStation::pair(UID, timeout);

  m_pRadio->openWritingPipe(0xaaaaaaaaaa);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, 0xaaaaaaaaab);
  m_pRadio->startListening();

  return bRetVal;
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
  uint16_t i = 0;

  m_pRadio->stopListening();

  while (i < len)
  {
    uint8_t size = 0;
    if (len > MAX_PAYLOAD_SIZE)
      size = MAX_PAYLOAD_SIZE;
    else
      size = len;

    m_pRadio->write(buf + i, size);
    i += size;
  }

  m_pRadio->startListening();

#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
  Serial.print(F("SENT: "));
  printArr(buf, (uint8_t)len);
  Serial.println();
#endif

  return 0;
}

int ThermoStation::available()
{
  return m_pRadio->available();
}

int ThermoStation::read(const void* buf, uint16_t len)
{
  if (available())
  {
    uint16_t size = m_pRadio->getDynamicPayloadSize();
    m_pRadio->read(buf, size);

#ifdef SERIAL_DEBUG
    Serial.println(__PRETTY_FUNCTION__);
    Serial.print("RECV: ");
    printArr(buf, (uint8_t)size);
    Serial.println();
#endif

    return size;
  }

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

void ThermoStation::printArr(void* buf, uint8_t len)
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
