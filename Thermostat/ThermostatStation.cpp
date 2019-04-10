#include "ThermostatStation.h"

ThermoStation::ThermoStation(uint8_t fanPin, uint8_t heatPin, uint8_t coolPin)
{
  //Set all of the control pins to outputs
  pinMode(fanPin, OUTPUT);
  pinMode(heatPin, OUTPUT);
  pinMode(coolPin, OUTPUT);

  //Turn off all of the outputs
  digitalWrite(fanPin, LOW);
  digitalWrite(heatPin, LOW);
  digitalWrite(coolPin, LOW);
}

ThermoStation::~ThermoStation()
{
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
