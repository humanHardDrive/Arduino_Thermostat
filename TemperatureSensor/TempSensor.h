#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

#include <RemoteSensor.h>
#include <Arduino.h>

#define SERIAL_DEBUG

#include "nRF24L01.h"
#include "RF24.h"
#include "msgs.h"
#include "FM25V10.h"

#include <SPI.h>

//Custom applicaiton messages
#define QUERY_TEMPERATURE   (USER_MSG_BASE + 0x00)
#define SET_POLLING_RATE    (USER_MSG_BASE + 0x01)
#define SET_REMOTE_RQST     (USER_MSG_BASE + 0x02)
#define SET_TEMP_RQST       (USER_MSG_BASE + 0x03)
#define SET_MODE_RQST       (USER_MSG_BASE + 0x04)

class TempSensor : public RemoteSensor
{
  public:
    TempSensor(byte tempSensePin);
    ~TempSensor();

    void addRadio(RF24* pRadio);
    void addMemoryDevice(FM25V10* pMemDevice, uint32_t nMemoryOffset);

    virtual bool recover();
    virtual void reset(bool nv);

    uint8_t GetTemperature();
    uint8_t GetMode();
    void SetTemperature(uint8_t temp);
    void SetMode(uint8_t mode);
    
    void begin();

    void background();

    void pair(uint16_t timeout);

  protected:
    uint32_t clockms();
    void print(const char* str);
    void print(int32_t num);
    void printArr(void* buf, uint8_t len);

    int write(const void* buffer, uint16_t len);
    int available();
    int read(const void* buffer, uint16_t len);

    virtual void save();

    void updateNetwork();

    void handleCommand(uint8_t cmd, const void* buffer, uint16_t len);

    virtual void seedRnd(uint16_t seed);
    virtual uint16_t rnd();

  private:
    void postTemperature();
    void takeTemperatureReading();

    void handleTemperatureQueryMsg(const void* buffer, uint16_t len);
    void handleSetPollingRateMsg(const void* buffer, uint16_t len);

  private:
    const uint64_t DISCOVERY_PIPE = 0x444953434F; //DISCO
    static const uint8_t MAX_PAYLOAD_SIZE = 32;

#ifdef SERIAL_DEBUG
    const uint32_t DEFAULT_POST_PERIOD = 5000;
#else
    const uint32_t DEFAULT_POST_PERIOD = (5*1000*60UL); //Default post reading every 5 minutes
#endif

    uint32_t m_nLastPostTime, m_nPostPeriod;
    uint32_t m_nMemoryOffset;

    const uint32_t SAMPLE_PERIOD = 50; //While awake, sample every 50ms
    const float ANALOG_VREF = 3.3;
    const float VOLT_PER_C = 0.01;
    static const uint8_t SAMPLE_AVERAGE_WINDOW = 10;
    
    byte m_nTempSensePin;
    uint32_t m_nLastSampleTime;
    uint16_t m_SampleWindow[SAMPLE_AVERAGE_WINDOW];
    uint8_t m_nCurrentTemp;

    RF24* m_pRadio;
    FM25V10* m_pMemoryDev;
};

#endif
