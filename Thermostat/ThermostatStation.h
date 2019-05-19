#ifndef __THERMOSTATION_H__
#define __THERMOSTATION_H__

#include <Arduino.h>

#define SERIAL_DEBUG

#define MAX_DISCOVERY   8

#include "BaseStation.h"
#include "MB85RS.h"
#include <DS3231.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "msgs.h"

#define NUM_TIME_DIV    4

//Custom applicaiton messages
#define QUERY_TEMPERATURE   (USER_MSG_BASE + 0x00)
#define SET_POLLING_RATE    (USER_MSG_BASE + 0x01)

class ThermoStation : public BaseStation
{
  public:
    ThermoStation();
    ~ThermoStation();

    void addRadio(RF24* pRadio);
    void begin();

    void setHeatMode(byte mode);
    void setFanMode(byte mode);

    void setTargetTemp(byte temp);
    byte getTargetTemp();

    void startDiscovery(uint32_t timeout);
    void stopDiscovery();

    void getDiscoveredDevice(uint8_t index, uint32_t* UID, char* name);

    void background(DateTime now);

    bool pair(uint32_t UID, uint32_t timeout);

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
    void print(int32_t num);
    void printArr(void* buf, uint8_t len);

    int write(const void* buf, uint16_t len);
    int available();
    int read(const void* buf, uint16_t len);

    void save(uint16_t addr, const void* buf, uint16_t len);
    void load(uint16_t addr, const void* buf, uint16_t len);

    void handleCommand(uint8_t cmd, uint32_t src, const void* buffer, uint16_t len);

  private:
    uint8_t dayofweek(DateTime date);

    void handleTempQuery(const void* buffer, uint16_t len);

  private:
    const uint64_t DISCOVERY_PIPE = 0x444953434F;
    static const uint8_t MAX_PAYLOAD_SIZE = 32;
    const uint8_t DEFAULT_RETRY_PERIOD = 50;

    struct TEMP_RULE
    {
      byte h, m;
      byte temp;
    };

    byte m_HeatMode, m_FanMode, m_TargetTemp, m_CurrentTemp;
    TEMP_RULE m_TempRules[2][ALL_HEAT_MODES][NUM_TIME_DIV];

    bool m_HeatOn, m_CoolOn;

    RF24* m_pRadio;
};

#endif
