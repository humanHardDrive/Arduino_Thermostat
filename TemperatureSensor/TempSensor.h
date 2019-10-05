#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

#include <Arduino.h>

//#define SERIAL_DEBUG

#include <SPI.h>

class TempSensor
{
  public:
    TempSensor(byte tempSensePin);
    ~TempSensor();

    uint8_t GetTemperature();
    uint8_t GetMode();
    void SetTemperature(uint8_t temp);
    void SetMode(uint8_t mode);

    void background();

  private:
    void postTemperature();
    void takeTemperatureReading();

  private:
#ifdef SERIAL_DEBUG
    const uint32_t DEFAULT_POST_PERIOD = 5000;
#else
    const uint32_t DEFAULT_POST_PERIOD = (5*1000*60UL); //Default post reading every 5 minutes
#endif

    uint32_t m_nLastPostTime, m_nPostPeriod;

    const uint32_t SAMPLE_PERIOD = 50; //While awake, sample every 50ms
    const float ANALOG_VREF = 3.3;
    const float VOLT_PER_C = 0.01;
    static const uint8_t SAMPLE_AVERAGE_WINDOW = 10;
    
    byte m_nTempSensePin;
    uint32_t m_nLastSampleTime;
    uint16_t m_SampleWindow[SAMPLE_AVERAGE_WINDOW];
    uint8_t m_nCurrentTemp;

    uint8_t m_nCoolMode, m_nFanMode;
};

#endif
