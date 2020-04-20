#ifndef __THERMOSTAT_DEVICE_H__
#define __THERMOSTAT_DEVICE_H__

#include "MemAccessor.h"
#include "MemDevice.h"

class ThermostatDevice : public MemAccessor
{
  public:
    static const uint8_t SCHEDULE_PER_DAY = 4;
  
    enum class HEAT_MODE
    {
      OFF,
      HEAT,
      COOL,
      ALL_HEAT_MODES
    };

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

    bool recover();

  private:
    struct ScheduleInfo
    {
      float fTargetTemp;
      uint8_t nHourStart, nMinuteStart;
    };

    MemDevice& m_MemDevice;
    ScheduleInfo m_Schedule[static_cast<uint8_t>(DAY_OF_WEEK::ALL_DAYS_OF_WEEK)][SCHEDULE_PER_DAY];
    
    bool m_bFanOn;
};

#endif
