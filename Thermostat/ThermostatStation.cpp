#include "ThermostatStation.h"

ThermoStation::ThermoStation(byte analogTempPin) :
  m_HeatMode(0),
  m_FanMode(0),
  m_HeatOn(false),
  m_CoolOn(false),
  m_pRadio(NULL),
  m_pMemoryDev(NULL),
  m_LocalTemp(72),
  m_RemoteTemp(72),
  m_analogTempPin(analogTempPin),
  m_bInCelsius(false),
  m_bUseRemote(false),
  m_nMemoryOffset(0)
{
  randomSeed(analogRead(analogTempPin));

  for (uint8_t i = 0; i < ALL_HEAT_MODES; i++)
  {
    for (uint8_t j = 0; j < NUM_TIME_DIV; j++)
    {
      m_TempRules[0][i][j].h = m_TempRules[1][i][j].h = (j + 1) * (23 / NUM_TIME_DIV);
      m_TempRules[0][i][j].m = m_TempRules[1][i][j].m = 0;
      m_TempRules[0][i][j].temp = m_TempRules[1][i][j].temp = 60 + (5 * j);
    }
  }

  m_pActiveRule = &m_TempRules[0][0][0];

  reset(false);
}

ThermoStation::~ThermoStation()
{
}

void ThermoStation::addRadio(RF24* pRadio)
{
  m_pRadio = pRadio;
}

void ThermoStation::addMemoryDevice(FM25V10* pMemDevice, uint32_t offset)
{
  m_pMemoryDev = pMemDevice;
  m_nMemoryOffset = offset;
}

void ThermoStation::begin()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  if (m_pRadio)
  {
    m_pRadio->begin();
    m_pRadio->enableDynamicPayloads();

    m_pRadio->openWritingPipe(m_SavedData.networkID);
    m_pRadio->openReadingPipe(1, m_SavedData.networkID);
    m_pRadio->setCRCLength(RF24_CRC_16);

    m_pRadio->startListening();
  }
}

void ThermoStation::setHeatMode(byte mode)
{
  if (mode < ALL_HEAT_MODES)
    m_HeatMode = mode;
}

byte ThermoStation::getHeatMode()
{
  return m_HeatMode;
}

void ThermoStation::setFanMode(byte mode)
{
  if (mode < ALL_FAN_MODES)
    m_FanMode = mode;
}

byte ThermoStation::getFanMode()
{
  return m_FanMode;
}

void ThermoStation::setTargetTemp(byte temp)
{
  m_TargetTemp = temp;
}

byte ThermoStation::getTargetTemp()
{
  return m_TargetTemp;
}

byte ThermoStation::getCurrentTemp()
{
  if (m_bUseRemote)
    return m_RemoteTemp;
  else
    return m_LocalTemp;
}

void ThermoStation::useRemoteSensor(bool use)
{
  m_bUseRemote = use;
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

  if (m_pRadio)
  {
    m_pRadio->stopListening();
    m_pRadio->openWritingPipe(DISCOVERY_PIPE);
    m_pRadio->closeReadingPipe(1);
    m_pRadio->openReadingPipe(1, DISCOVERY_PIPE);

    BaseStation::startDiscovery(timeout);
  }
}

void ThermoStation::stopDiscovery()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  if (m_pRadio)
  {
    m_pRadio->stopListening();
    m_pRadio->openWritingPipe(m_SavedData.networkID);
    m_pRadio->closeReadingPipe(1);
    m_pRadio->openReadingPipe(1, m_SavedData.networkID);
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

//This call is blocking until the timeout
bool ThermoStation::pair(uint32_t UID, char* sName, uint32_t timeout)
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  bool bRetVal = false;

  if (m_pRadio)
  {
    m_pRadio->openWritingPipe(DISCOVERY_PIPE);
    m_pRadio->closeReadingPipe(1);
    m_pRadio->openReadingPipe(1, DISCOVERY_PIPE);
    m_pRadio->stopListening();

    //This call is blocking until the timeout
    bRetVal = BaseStation::pair(UID, sName, timeout);

    m_pRadio->openWritingPipe(m_SavedData.networkID);
    m_pRadio->closeReadingPipe(1);
    m_pRadio->openReadingPipe(1, m_SavedData.networkID);
    m_pRadio->startListening();
  }
  return bRetVal;
}

void ThermoStation::background(const DateTime& t)
{
  BaseStation::background();

  updateSchedule(t);
  updateHeatState();
  updateLocalTemp();
}

void ThermoStation::updateSchedule(const DateTime& t)
{
  byte day = dayofweek(t);
  byte isWeekend = 0;

  if (day == SATURDAY || day == SUNDAY)
    isWeekend = 1;

  for (byte i = 0; i < NUM_TIME_DIV; i++)
  {
    TEMP_RULE rule = m_TempRules[isWeekend][m_HeatMode][i];

    if (t.hour() > rule.h || t.minute() > rule.m)
      m_pActiveRule = &m_TempRules[isWeekend][m_HeatMode][i];
  }

  m_TargetTemp = m_pActiveRule->temp;
}

void ThermoStation::updateHeatState()
{
  if (m_HeatMode == HEAT)
  {
    if (!m_HeatOn)
    {
      if (getCurrentTemp() < m_TargetTemp)
      {
        if ((millis() - m_nTimeLastCrossedThresh) > m_nOnHysteresis)
          m_HeatOn = true;
      }
      else
        m_nTimeLastCrossedThresh = millis();
    }
    else
    {
      if (getCurrentTemp() > m_TargetTemp)
      {
        if ((millis() - m_nTimeLastCrossedThresh) > m_nOffHysteresis)
          m_HeatOn = false;
      }
      else
        m_nTimeLastCrossedThresh = millis();
    }
  }
  else if (m_HeatMode == COOL)
  {
    if (!m_CoolOn)
    {
      if (getCurrentTemp() > m_TargetTemp)
      {
        if ((millis() - m_nTimeLastCrossedThresh) > m_nOnHysteresis)
          m_CoolOn = true;
      }
      else
        m_nTimeLastCrossedThresh = millis();
    }
    else
    {
      if (getCurrentTemp() < m_TargetTemp)
      {
        if ((millis() - m_nTimeLastCrossedThresh) > m_nOffHysteresis)
          m_CoolOn = false;
      }
      else
        m_nTimeLastCrossedThresh = millis();
    }
  }
}

void ThermoStation::updateLocalTemp()
{
  if ((millis() - m_nLastTempSampleTime) > SAMPLE_DELAY)
  {
    m_nLastTempSampleTime = millis();
  }
}

static uint8_t ThermoStation::dayofweek(const DateTime& date)
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

  if (m_pRadio)
  {
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

    return len;
  }

  return 0;
}

int ThermoStation::available()
{
  if (m_pRadio)
  {
    //Handle corrupt dynamic payloads
    if (!m_pRadio->getDynamicPayloadSize())
      return 0;

    return m_pRadio->available();
  }
  return 0;
}

int ThermoStation::read(const void* buf, uint16_t len)
{
  if (m_pRadio)
  {
    if (m_pRadio->available())
    {
      uint8_t size = m_pRadio->getDynamicPayloadSize();
      if (size > len)
        size = len;

      if (size)
      {
        m_pRadio->read(buf, size);

#ifdef SERIAL_DEBUG
        Serial.println(__PRETTY_FUNCTION__);
        Serial.print("RECV: ");
        printArr(buf, (uint8_t)size);
        Serial.println();
#endif
      }
      return size;
    }
  }
  return 0;
}

bool ThermoStation::recover()
{
  if (m_pMemoryDev)
  {
    m_pMemoryDev->read(BASE_STATION_DATA_OFFSET + m_nMemoryOffset, (uint8_t*)&m_SavedData, sizeof(m_SavedData));
    uint16_t calcChkSum = calcChecksum((uint8_t*)&m_SavedData, sizeof(m_SavedData) - 2); //Don't include the checksum in the calculation

    if (m_SavedData.checksum == calcChkSum)
    {
      if (!m_SavedData.UID)
        return false;

      return true;
    }
  }

  return false;
}

void ThermoStation::reset(bool nv)
{
  memset(&m_SavedData, 0, sizeof(m_SavedData));

  m_SavedData.UID = random(65535) + 1;
  m_SavedData.UID *= random(65535) + 1;

  for (uint8_t i = 0; i < NETWORK_LEGNTH; i++)
    m_SavedData.networkID[i] = random(256);

  if (nv)
    save();
}

void ThermoStation::save()
{
  if (m_pMemoryDev)
  {
    m_SavedData.checksum = calcChecksum((uint8_t*)&m_SavedData, sizeof(m_SavedData) - 2); //Don't include the checksum in the calculation
    
    m_pMemoryDev->write(BASE_STATION_DATA_OFFSET + m_nMemoryOffset, (uint8_t*)&m_SavedData, sizeof(m_SavedData));
    m_pMemoryDev->write(SCHEDULE_DATA_OFFSET + m_nMemoryOffset, (uint8_t*)&m_TempRules, sizeof(m_TempRules));
  }
}

void ThermoStation::handleCommand(uint8_t cmd, uint32_t src, const void* buffer, uint16_t len)
{
  switch (cmd)
  {
    case QUERY_TEMPERATURE:
      handleTempQuery(src, buffer, len);
      break;
  }

  BaseStation::handleCommand(cmd, src, buffer, len);
}

void ThermoStation::handleTempQuery(uint32_t src, const void* buffer, uint16_t len)
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  uint8_t curTemp = *((uint8_t*)buffer);

#ifdef SERIAL_DEBUG
  Serial.print(F("TEMP: "));
  Serial.print((int)curTemp);
  Serial.println();
#endif
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

