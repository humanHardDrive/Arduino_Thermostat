#ifndef __THERMOSTATION_H__
#define __THERMOSTATION_H__

#include <Arduino.h>

//#define SERIAL_DEBUG

#include "BaseStation.h"
#include "FM25V10.h"
#include <DS3231.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "msgs.h"

#define NUM_TIME_DIV    4

#define NUM_SAMPLES   15
#define SAMPLE_DELAY  1000

//Custom applicaiton messages
#define QUERY_TEMPERATURE   (USER_MSG_BASE + 0x00)
#define SET_POLLING_RATE    (USER_MSG_BASE + 0x01)

class ThermoStation : public BaseStation
{
  public:
    ThermoStation(byte analotTempPin);
    ~ThermoStation();

    void addRadio(RF24* pRadio);
    void addMemoryDevice(FM25V10* pMemDevice, uint32_t offset);
    void begin();

    virtual bool recover();
    virtual void reset(bool nv);

    void setHeatMode(byte mode);
    void setFanMode(byte mode);

    byte getHeatMode();
    byte getFanMode();

    void setTargetTemp(byte temp);
    byte getTargetTemp();

    byte getCurrentTemp();
    void useRemoteSensor(bool use);

    void startDiscovery(uint32_t timeout);
    void stopDiscovery();

    void getDiscoveredDevice(uint8_t index, uint32_t* UID, char* name);

    void background(const DateTime& now);

    bool pair(uint32_t UID, char* sName, uint32_t timeout);

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

  protected:
    uint32_t clockms();
    void print(const char* str);
    void print(int32_t num);
    void printArr(void* buf, uint8_t len);

    int write(const void* buf, uint16_t len);
    int available();
    int read(const void* buf, uint16_t len);

    virtual void save();

    void handleCommand(uint8_t cmd, uint32_t src, const void* buffer, uint16_t len);

  private:
    void handleTempQuery(uint32_t src, const void* buffer, uint16_t len);

    void updateLocalTemp();
    void updateSchedule(const DateTime& t);
    void updateHeatState();

  private:
    const uint64_t DISCOVERY_PIPE = 0x444953434F;
    static const uint8_t MAX_PAYLOAD_SIZE = 32;

    static const uint64_t BASE_STATION_DATA_OFFSET = 0;
    static const uint64_t SCHEDULE_DATA_OFFSET = BASE_STATION_DATA_OFFSET + sizeof(m_SavedData);

    uint16_t m_LocalTempSample[NUM_SAMPLES];
    uint32_t m_nLastTempSampleTime = 0;
    byte m_analogTempPin;
    bool m_bInCelsius;

    struct TEMP_RULE
    {
      byte h, m;
      byte temp;
    };

    uint32_t m_nOnHysteresis = (uint32_t)(5*60*1000), m_nOffHysteresis = (uint32_t)(5*60*1000);
    uint32_t m_nTimeLastCrossedThresh;

    byte m_HeatMode, m_FanMode, m_TargetTemp, m_LocalTemp, m_RemoteTemp;
    TEMP_RULE m_TempRules[2][ALL_HEAT_MODES][NUM_TIME_DIV];
    TEMP_RULE *m_pActiveRule;

    bool m_HeatOn, m_CoolOn, m_bUseRemote;

    RF24* m_pRadio;
    FM25V10* m_pMemoryDev;
    uint32_t m_nMemoryOffset;
};

#endif
