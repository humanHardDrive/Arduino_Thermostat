#include "ThermostatStation.h"

ThermoStation::ThermoStation() :
  m_HeatMode(0),
  m_FanMode(0),
  m_HeatOn(false),
  m_CoolOn(false)
{
}

ThermoStation::~ThermoStation()
{
}

void ThermoStation::setHeatMode(byte mode)
{
  if(mode < ALL_HEAT_MODES)
    m_HeatMode = mode;
}

void ThermoStation::setFanMode(byte mode)
{
  if(mode < ALL_FAN_MODES)
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

void ThermoStation::background(DateTime t)
{
  BaseStation::background();

  byte day = SATURDAY;
  byte isWeekend = 0;

  if(day == SATURDAY || day == SUNDAY)
    isWeekend = 1;

  for(byte i = 0; i < NUM_TIME_DIV; i++)
  {
    TEMP_RULE rule = m_TempRules[isWeekend][m_HeatMode][i];
    
    if(t.hour() > rule.h || t.minute() > rule.m)
      m_TargetTemp = rule.temp;
  }
}

int ThermoStation::write(const void* buf, uint16_t len)
{
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
  Serial.print(str);
}
