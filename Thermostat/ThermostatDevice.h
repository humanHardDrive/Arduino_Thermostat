#ifndef __THERMOSTAT_DEVICE_H__
#define __THERMOSTAT_DEVICE_H__

#include "MemAccessor.h"
#include "MemDevice.h"

class ThermostatDevice : public MemAccessor
{
  public:
    enum class DAY_OF_WEEK
    {
      SUNDAY,
      MONDAY,
      TUESDAY,
      WEDNESDAY,
      THURSDAY,
      FRIDAY,
      SATURDAY,
      ALL_DAYS_OF_WEEK
    };
  
    ThermostatDevice(MemDevice& memDevice);

    void update(DAY_OF_WEEK day, uint8_t nHour, uint8_t nMinute);

  private:
    MemDevice& m_MemDevice;
};

#endif
