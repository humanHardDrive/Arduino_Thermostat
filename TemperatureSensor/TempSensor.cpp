#include "TempSensor.h"

TempSensor::TempSensor(byte tempSensePin) :
  m_nTempSensePin(tempSensePin),
  m_nCurrentTemp(72)
{
  seedRnd(analogRead(0));
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

void TempSensor::addRadio(RF24* pRadio)
{
  m_pRadio = pRadio;
}

void TempSensor::addMemoryDevice(FM25V10* pMemDevice, uint32_t nMemoryOffset)
{
  m_pMemoryDev = pMemDevice;
}

bool TempSensor::recover()
{

}

void TempSensor::reset(bool nv)
{

}

void TempSensor::save()
{

}

void TempSensor::begin()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  m_pRadio->begin();
  m_pRadio->enableDynamicPayloads();
  m_pRadio->startListening();
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
  if (!m_bInDiscovery &&
      (millis() - m_nLastPostTime) > m_nPostPeriod)
  {
    postTemperature();
    m_nLastPostTime = millis();
  }
  else if (m_bInDiscovery)
    m_nLastPostTime = millis();

  takeTemperatureReading();
  RemoteSensor::background();
}

void TempSensor::pair(uint16_t timeout)
{
  m_pRadio->stopListening();
  m_pRadio->openWritingPipe(DISCOVERY_PIPE);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, DISCOVERY_PIPE);
  m_pRadio->startListening();

  RemoteSensor::pair(timeout);
}

uint16_t TempSensor::rnd()
{
  return (uint16_t)random(0, 0xFFFF);
}

void TempSensor::seedRnd(uint16_t seed)
{
  randomSeed(seed);
}

uint32_t TempSensor::clockms()
{
  return millis();
}

int TempSensor::write(const void* buffer, uint16_t len)
{
  uint16_t i = 0;

  m_pRadio->stopListening();

  while (i < len)
  {
    uint8_t size = 0;
    if (len > MAX_PAYLOAD_SIZE)
      size = MAX_PAYLOAD_SIZE;
    else
      size = len;

    m_pRadio->write(buffer + i, size);
    i += size;
  }

  m_pRadio->startListening();

#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
  Serial.print(F("SENT: "));
  printArr(buffer, (uint8_t)len);
  Serial.println();
#endif

  return len;
}

int TempSensor::available()
{
  //Handle corrupt dynamic payloads
  if (!m_pRadio->getDynamicPayloadSize())
    return 0;

  return m_pRadio->available();
}

int TempSensor::read(const void* buffer, uint16_t len)
{
  if (available())
  {
    uint16_t size = m_pRadio->getDynamicPayloadSize();
    m_pRadio->read(buffer, size);

#ifdef SERIAL_DEBUG
    Serial.println(__PRETTY_FUNCTION__);
    Serial.print("RECV: ");
    printArr(buffer, (uint8_t)size);
    Serial.println();
#endif

    return size;
  }

  return 0;
}

void TempSensor::updateNetwork()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  m_pRadio->stopListening();
  m_pRadio->openWritingPipe(m_SavedData.networkID);
  m_pRadio->closeReadingPipe(1);
  m_pRadio->openReadingPipe(1, m_SavedData.networkID);
  m_pRadio->startListening();
}

void TempSensor::handleCommand(uint8_t cmd, const void* buffer, uint16_t len)
{
  switch (cmd)
  {
    case QUERY_TEMPERATURE:
      handleTemperatureQueryMsg(buffer, len);
      break;

    case SET_POLLING_RATE:
      handleSetPollingRateMsg(buffer, len);
      break;

    case SET_REMOTE_RQST:
      break;

    case SET_TEMP_RQST:
      break;

    case SET_MODE_RQST:
      break;

    case GET_MODE_MSG:
      break;
  }

  //Need to call this so that the discovery messages are handled by base class
  RemoteSensor::handleCommand(cmd, buffer, len);
}

void TempSensor::postTemperature()
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  uint8_t buf[16];
  uint16_t len;
  uint8_t curTemp = 72;

  buildPacket((uint8_t)(QUERY_TEMPERATURE), &m_nMsgID, m_SavedData.UID, (uint8_t)0,
              (uint8_t*)&curTemp, (uint16_t)1, buf, &len);
  write(buf, len);
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

void TempSensor::handleTemperatureQueryMsg(const void* buffer, uint16_t len)
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  //Update the last sample time to sample in 50ms
  m_nLastPostTime = millis() - (m_nPostPeriod - 50);
}

void TempSensor::handleSetPollingRateMsg(const void* buffer, uint16_t len)
{
#ifdef SERIAL_DEBUG
  Serial.println(__PRETTY_FUNCTION__);
#endif

  memcpy(&m_nPostPeriod, buffer, sizeof(m_nPostPeriod)); //Update the period
  m_nLastPostTime = millis(); //Reset the sample timer
}

void TempSensor::print(const char* str)
{
#ifdef SERIAL_DEBUG
  Serial.println(str);
#endif
}

void TempSensor::print(int32_t num)
{
#ifdef SERIAL_DEBUG
  Serial.println(num);
#endif
}

void TempSensor::printArr(void* buf, uint8_t len)
{

  for (uint8_t i = 0; i < len; i++)
  {
    byte b = ((byte*)buf)[i];

    Serial.print("0x");
    if (b <= 0x0F)
      Serial.print('0');

    Serial.print(b, HEX);
    Serial.print(' ');
  }
  Serial.println();
}
