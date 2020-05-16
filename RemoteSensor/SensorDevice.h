#ifndef __SENSOR_DEVICE_H__
#define __SENSOR_DEVICE_H__

#include <Arduino.h>
#include "MemAccessor.h"

class SensorDevice : public MemAccessor
{
  public:
    SensorDevice(uint8_t tempSensePin, uint32_t nSamplePeriod);

    void update();

    float getCurrentTemp() { return (m_bUseFahrenheit ? m_fCurrentTempF : m_fCurrentTempC); }

    static constexpr float ANALOG_REFERENCE = 3.3;
    static const uint16_t ANALOG_RESOLUTION = 1024;
    static const uint8_t SAMPLE_WINDOW = 8;

  private:
    static float VtoC(float fV);
    static float CtoF(float fC);
  
    uint8_t m_nAnalogPin;
    uint32_t m_nSamplePeriod, m_nLastSampleTime;
    uint16_t m_nSampleFilter[SAMPLE_WINDOW];
    float m_fCurrentTempC, m_fCurrentTempF;
    bool m_bUseFahrenheit;
};

#endif
