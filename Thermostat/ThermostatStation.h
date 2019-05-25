#ifndef __THERMOSTATION_H__
#define __THERMOSTATION_H__

#include <Arduino.h>

//#define SERIAL_DEBUG

#include "BaseStation.h"
#include "MB85RS.h"
#include <DS3231.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "msgs.h"

#define NUM_TIME_DIV    4

#define NUM_SAMPLES   15
#define SAMPLE_DELAY  100

//Custom applicaiton messages
#define QUERY_TEMPERATURE   (USER_MSG_BASE + 0x00)
#define SET_POLLING_RATE    (USER_MSG_BASE + 0x01)

class ThermoStation : public BaseStation
{
  public:
    ThermoStation(byte analotTempPin);
    ~ThermoStation();

    void addRadio(RF24* pRadio);
    void begin();

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

    void save(uint16_t addr, const void* buf, uint16_t len);
    void load(uint16_t addr, const void* buf, uint16_t len);

    void handleCommand(uint8_t cmd, uint32_t src, const void* buffer, uint16_t len);

  private:
    void handleTempQuery(uint32_t src, const void* buffer, uint16_t len);

    void updateLocalTemp();

  private:
    const uint64_t DISCOVERY_PIPE = 0x444953434F;
    static const uint8_t MAX_PAYLOAD_SIZE = 32;
    const uint8_t DEFAULT_RETRY_PERIOD = 50;
  
    const float TABLE_OFFSET = -40.0;
    float rTable[39] =
    {
      166.047, 119.950, 87.600, 64.643, 48.179, 46.250, 27.523, 21.078,
      16.277, 12.669, 9.936, 7.849, 6.244, 5.000, 4.030, 3.267, 2.665,
      2.186, 1.803, 1.494, 1.245, 1.042, 0.8765, 0.7405, 0.6282, 0.5352,
      0.4577, 0.393, 0.3386, 0.2929, 0.2542, 0.2213, 0.1933, 0.1694,
      0.1488, 0.1312, 0.116, 0.1028, 0.09132
    };

    uint16_t m_LocalTempSample[NUM_SAMPLES];
    uint32_t m_nLastTempSampleTime = 0;
    byte m_analogTempPin;
    bool m_bInCelsius;

    struct TEMP_RULE
    {
      byte h, m;
      byte temp;
    };

    byte m_HeatMode, m_FanMode, m_TargetTemp, m_LocalTemp, m_RemoteTemp;
    TEMP_RULE m_TempRules[2][ALL_HEAT_MODES][NUM_TIME_DIV];
    TEMP_RULE *m_pActiveRule;

    bool m_HeatOn, m_CoolOn, m_bUseRemote;

    RF24* m_pRadio;
};

#endif
