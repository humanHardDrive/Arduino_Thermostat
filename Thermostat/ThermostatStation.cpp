#include "ThermostatStation.h"

ThermoStation::ThermoStation() :
  m_HeatMode(0),
  m_FanMode(0)
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

void ThermoStation::background()
{
  BaseStation::background();
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
