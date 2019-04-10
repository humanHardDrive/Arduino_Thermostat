#ifndef __THERMOSTATION_H__
#define __THERMOSTATION_H__

#include "BaseStation.h"

class ThermoStation : public BaseStation
{
  public:
  ThermoStation();
  ~ThermoStation();

  int write(const void* buf, uint16_t len);
  uint32_t clockms();
};

#endif
