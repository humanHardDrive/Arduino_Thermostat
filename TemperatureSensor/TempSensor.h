#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

#include <RemoteSensor.h>
#include <Arduino.h>

#define SERIAL_DEBUG

#include "nRF24L01.h"
#include "RF24.h"
#include "msgs.h"

#include <SPI.h>

//Custom applicaiton messages
#define QUERY_TEMPERATURE   (USER_MSG_BASE + 0x00)
#define SET_POLLING_RATE    (USER_MSG_BASE + 0x01)

class TempSensor : public RemoteSensor
{
  public:
    TempSensor();
    ~TempSensor();

    void addRadio(RF24* pRadio);
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

    void save(uint16_t addr, const void* buffer, uint16_t len);
    void load(uint16_t addr, const void* buffer, uint16_t len);

    void handleCommand(uint8_t cmd, const void* buffer, uint16_t len);

    virtual void seedRnd(uint16_t seed);
    virtual uint16_t rnd();

  private:
    void sampleAndSend();

    void handleTemperatureQueryMsg(const void* buffer, uint16_t len);
    void handleSetPollingRateMsg(const void* buffer, uint16_t len);

  private:
    const uint64_t DISCOVERY_PIPE = 0x444953434F; //DISCO
    static const uint8_t MAX_PAYLOAD_SIZE = 32;

#ifdef SERIAL_DEBUG
    const uint32_t DEFAULT_SAMPLE_PERIOD = 5000;
#else
    const uint32_t DEFAULT_SAMPLE_PERIOD = (5*1000*60); //Default sample every 5 minutes
#endif

    uint32_t m_u32LastSampleTime, m_u32SamplePeriod;

    RF24* m_pRadio;
};

#endif
