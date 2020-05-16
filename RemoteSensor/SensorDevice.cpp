#include "SensorDevice.h"

SensorDevice::SensorDevice(uint8_t tempSensePin, uint32_t nSamplePeriod) :
  m_nAnalogPin(tempSensePin),
  m_nSamplePeriod(nSamplePeriod),
  m_nLastSampleTime(0),
  m_fCurrentTempC(25.0),
  m_fCurrentTempF(CtoF(m_fCurrentTempC))
{
  /*Set filter to an average of 25°C*/
  for (uint8_t i = 0; i < SAMPLE_WINDOW; i++)
    m_nSampleFilter[i] = (uint16_t)(0.75 * ANALOG_RESOLUTION / ANALOG_REFERENCE);
}

void SensorDevice::update()
{
  if ((millis() - m_nLastSampleTime) > m_nSamplePeriod)
  {
    for (uint8_t i = 0; i < (SAMPLE_WINDOW - 1); i++)
      m_nSampleFilter[i + 1] = m_nSampleFilter[i];

    m_nSampleFilter[0] = analogRead(m_nAnalogPin);

    float fAverage = 0;
    for (uint8_t i = 0; i < SAMPLE_WINDOW; i++)
      fAverage += m_nSampleFilter[i];

    fAverage /= SAMPLE_WINDOW;
    fAverage = fAverage * ANALOG_REFERENCE / ANALOG_RESOLUTION; /*Convert to volts*/

    m_fCurrentTempC = VtoC(fAverage);
    m_fCurrentTempF = CtoF(m_fCurrentTempC);
  }
}

float SensorDevice::VtoC(float fV)
{
  return ((fV - 0.5) * 100);
}

float SensorDevice::CtoF(float fC)
{
  return (((fC * 9) / 5) + 32);
}
