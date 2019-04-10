#include "ThermostatStation.h"

#include <Arduino.h>

ThermoStation::ThermoStation()
{ 
}

ThermoStation::~ThermoStation()
{
}

int ThermoStation::write(const void* buf, uint16_t len)
{
  return 0;
}

uint32_t ThermoStation::clockms()
{
  return millis();
}

