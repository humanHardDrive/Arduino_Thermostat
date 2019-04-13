#ifndef __THERMOSTATION_H__
#define __THERMOSTATION_H__

#include "BaseStation.h"
#include "MB85RS.h"

#include <Arduino.h>

class ThermoStation : public BaseStation
{
  public:
  ThermoStation();
  ~ThermoStation();

  protected:
  uint32_t clockms();
  void print(const char* str);
  
  int write(const void* buf, uint16_t len);
  int available();
  int read(const void* buf, uint16_t len);
  
  void save(uint16_t addr, const void* buf, uint16_t len);
  void load(uint16_t addr, const void* buf, uint16_t len);
};

#endif
