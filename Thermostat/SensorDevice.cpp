#include "SensorDevice.h"

SensorDevice::SensorDevice(uint8_t tempSensePin, uint32_t nSamplePeriod, uint32_t nPublishPeriod) :
  m_nAnalogPin(tempSensePin),
  m_nSamplePeriod(nSamplePeriod),
  m_nPublishPeriod(nPublishPeriod),
  m_bShouldPublish(false),
  m_fCurrentTempC(25.0),
  m_fCurrentTempF(77)
{
  /*Set filter to an average of 25°C*/
  for(uint8_t i = 0; i < SAMPLE_WINDOW; i++)
    m_nSampleFilter[i] = (uint16_t)(0.75 * ANALOG_RESOLUTION / ANALOG_REFERENCE);
}
