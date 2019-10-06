#include "ThermostatStation.h"

ThermoStation::ThermoStation(byte analogTempPin) :
  m_HeatMode(0),
  m_FanMode(0),
  m_bUseSchedule(true),
  m_HeatOn(false),
  m_CoolOn(false),
  m_LocalTemp(72),
  m_analogTempPin(analogTempPin)
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
}

ThermoStation::~ThermoStation()
{
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
  if (temp > MAX_TEMP)
    temp = MAX_TEMP;
  else if (temp < MIN_TEMP)
    temp = MIN_TEMP;

  m_TargetTemp = temp;
}

byte ThermoStation::getTargetTemp()
{
  return m_TargetTemp;
}

byte ThermoStation::getCurrentTemp()
{
    return m_LocalTemp;
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

void ThermoStation::background(const uint8_t& nDayOfWeek, const uint8_t& nHour, const uint8_t& nMinute)
{
  if (m_bUseSchedule)
    updateSchedule(nDayOfWeek, nHour, nMinute);

  updateHeatState();
  updateLocalTemp();
}

void ThermoStation::updateSchedule(const uint8_t& nDayOfWeek, const uint8_t& nHour, const uint8_t& nMinute)
{
  bool isWeekend = (nDayOfWeek == SATURDAY || nDayOfWeek == SUNDAY);
  for (byte i = 0; i < NUM_TIME_DIV; i++)
  {
    TEMP_RULE rule = m_TempRules[isWeekend][m_HeatMode][i];

    if (nHour > rule.h || nMinute > rule.m)
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
    float average = 0;

    for (uint8_t i = 1; i < NUM_SAMPLES; i++)
    {
      average += m_LocalTempSample[i];
      m_LocalTempSample[i] = m_LocalTempSample[i - 1];
    }

    m_LocalTempSample[0] = analogRead(m_analogTempPin);
    average += m_LocalTempSample[0];
    average /= NUM_SAMPLES;

    average = (average / 1023.0) * VREF; //Convert to volts
    average /= VOLT_PER_C; //Converts to degrees C
    average = ((average * 9) / 5) + 32; //Convert to degrees F
    average += 0.5; //Round

    m_LocalTemp = (uint8_t)average;

    m_nLastTempSampleTime = millis();
  }
}
