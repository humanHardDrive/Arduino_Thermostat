#ifndef __THERMOSTATION_H__
#define __THERMOSTATION_H__

#include "BaseStation.h"
#include "MB85RS.h"
#include <DS3231.h>

#include <Arduino.h>

#define NUM_TIME_DIV    4

class ThermoStation : public BaseStation
{
  public:
  ThermoStation();
  ~ThermoStation();

  void setHeatMode(byte mode);
  void setFanMode(byte mode);

  void setTargetTemp(byte temp);
  byte getTargetTemp();

  void background(DateTime now);

  bool isFanOn();
  bool isHeatOn();
  bool isCoolOn();

  public:
  enum HEAT_MODE
  {
    OFF = 0,
    HEAT,
    COOL,
    ALL_HEAT_MODES
  };

  enum FAN_MODE
  {
    AUTO = 0,
    ON,
    ALL_FAN_MODES
  };

  enum DAY_OF_WEEK
  {
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
  };

  protected:
  uint32_t clockms();
  void print(const char* str);
  
  int write(const void* buf, uint16_t len);
  int available();
  int read(const void* buf, uint16_t len);
  
  void save(uint16_t addr, const void* buf, uint16_t len);
  void load(uint16_t addr, const void* buf, uint16_t len);

  private:
  struct TEMP_RULE
  {
    byte h, m;
    byte temp;
  };
  
  byte m_HeatMode, m_FanMode, m_TargetTemp;
  TEMP_RULE m_TempRules[2][ALL_HEAT_MODES][NUM_TIME_DIV];

  bool m_HeatOn, m_CoolOn;
};

#endif
