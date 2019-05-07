#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

#include <RemoteSensor.h>
#include <Arduino.h>

#define SERIAL_DEBUG

#include "nRF24L01.h"
#include "RF24.h"

#include <SPI.h>

class TempSensor : public RemoteSensor
{
  public:
    TempSensor();
    ~TempSensor();

    void addRadio(RF24* pRadio);
    void begin();

    void pair();

  protected:
    uint32_t clockms();
    void print(const char* str);
    void printArr(void* buf, uint8_t len);

    int write(const void* buffer, uint16_t len);
    int available();
    int read(const void* buffer, uint16_t len);

    void save(uint16_t addr, const void* buffer, uint16_t len);
    void load(uint16_t addr, const void* buffer, uint16_t len);

  private:
    const uint8_t discoveryPipe[6] = {"DISCO"};

    RF24* m_pRadio;
};

#endif
