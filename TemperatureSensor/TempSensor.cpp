#include "TempSensor.h"

TempSensor::TempSensor(byte tempSensePin) :
  m_nTempSensePin(tempSensePin),
  m_nCurrentTemp(72)
{
  analogReference(DEFAULT);

  m_nLastSampleTime = millis();
  m_nPostPeriod = DEFAULT_POST_PERIOD;

  //Default the filter to 72 degrees
  for (uint8_t i = 0; i < SAMPLE_AVERAGE_WINDOW; i++)
    m_SampleWindow[i] = 72;
}

TempSensor::~TempSensor()
{

}


uint8_t TempSensor::GetTemperature()
{
  return m_nCurrentTemp;
}

uint8_t TempSensor::GetMode()
{
  return m_nCoolMode;
}

void TempSensor::SetTemperature(uint8_t temp)
{

}

void TempSensor::SetMode(uint8_t mode)
{

}

void TempSensor::background()
{
  takeTemperatureReading();
}

void TempSensor::takeTemperatureReading()
{
  if ((millis() - m_nLastSampleTime) > SAMPLE_PERIOD)
  {
    for (uint8_t i = 1; i < SAMPLE_AVERAGE_WINDOW; i++)
      m_SampleWindow[i] = m_SampleWindow[i - 1];

    m_SampleWindow[0] = analogRead(m_nTempSensePin);

    float average = 0;
    for (uint8_t i = 0; i < SAMPLE_AVERAGE_WINDOW; i++)
      average += m_SampleWindow[i];
    average /= SAMPLE_AVERAGE_WINDOW;

    average = (average / 1023.0) * ANALOG_VREF; //Convert to voltage
    average -= 0.5;
    average /= VOLT_PER_C; //Convert to degrees Celsius
    average = ((average * 9) / 5) + 32; //Convert to fahrenheit
    average += 0.5; //Round

    m_nCurrentTemp = (uint8_t)average;
  }
}

void TempSensor::postTemperature()
{
}
