#ifndef __THERMOSTATION_H__
#define __THERMOSTATION_H__

#include <Arduino.h>

//#define SERIAL_DEBUG

#include <DS3231.h>
#include <SPI.h>

#define NUM_TIME_DIV    4

#define NUM_SAMPLES   15
#define SAMPLE_DELAY  1000

#define MAX_TEMP  90
#define MIN_TEMP  60

//Custom applicaiton messages
#define QUERY_TEMPERATURE   (USER_MSG_BASE + 0x00)
#define SET_POLLING_RATE    (USER_MSG_BASE + 0x01)
#define SET_REMOTE_RQST     (USER_MSG_BASE + 0x02)

class ThermoStation
{
  public:
    ThermoStation(byte analotTempPin);
    ~ThermoStation();

    void setHeatMode(byte mode);
    void setFanMode(byte mode);

    byte getHeatMode();
    byte getFanMode();

    void enableSchedule() {m_bUseSchedule = true;}
    void disableSchedule() {m_bUseSchedule = false;}

    bool usingSchedule() const {return m_bUseSchedule;}

    void setTargetTemp(byte temp);
    byte getTargetTemp();

    byte getCurrentTemp();

    void startDiscovery(uint32_t timeout);
    void stopDiscovery();

    void getDiscoveredDevice(uint8_t index, uint32_t* UID, char* name);
    void getTemperatureDevice(uint8_t index, char* name, char* reading);

    void background(const uint8_t& nDayOfWeek, const uint8_t& nHour, const uint8_t& nMinute);

    bool isFanOn();
    bool isHeatOn();
    bool isCoolOn();

    static uint8_t dayofweek(const DateTime& date);

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

  private:
    void updateLocalTemp();
    void updateSchedule(const uint8_t& nDayOfWeek, const uint8_t& nHour, const uint8_t& nMinute);
    void updateHeatState();

  private:
    const float VOLT_PER_C = 0.01;
    const float VREF = 3.3;

    uint16_t m_LocalTempSample[NUM_SAMPLES];
    uint32_t m_nLastTempSampleTime = 0;
    byte m_analogTempPin;

    struct TEMP_RULE
    {
      byte h, m;
      byte temp;
    };

    uint32_t m_nOnHysteresis = (uint32_t)(5*60*1000), m_nOffHysteresis = (uint32_t)(5*60*1000);
    uint32_t m_nTimeLastCrossedThresh;

    byte m_HeatMode, m_FanMode, m_TargetTemp, m_LocalTemp;
    TEMP_RULE m_TempRules[2][ALL_HEAT_MODES][NUM_TIME_DIV];
    TEMP_RULE *m_pActiveRule;

    bool m_HeatOn, m_CoolOn, m_bUseSchedule;
};

#endif
