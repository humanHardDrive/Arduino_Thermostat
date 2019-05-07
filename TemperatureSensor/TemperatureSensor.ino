#include "TempSensor.h"

#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#include <SPI.h>

#define APP_NAME  F("REMOTE TEMPERATURE SENSOR")
#define VERSION   F("v0.0")

#define SERIAL_DEBUG

#define RF24_CS_PIN   10
#define RF24_CE_PIN   9

RF24 radio(RF24_CE_PIN, RF24_CS_PIN);
TempSensor temperatureSensor;

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
  printf_begin();
  Serial.println(APP_NAME);
  Serial.println(VERSION);
  Serial.println();
#endif

  SPI.begin();

  if (!radio.isChipConnected())
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to connect to radio..."));
#endif
    while (1);
  }

  //Start the sensorr object
  temperatureSensor.addRadio(&radio);
  temperatureSensor.begin();

#ifdef SERIAL_DEBUG
  radio.printDetails();
  Serial.println();
#endif
}

void loop()
{
  temperatureSensor.background();

#ifdef SERIAL_DEBUG
  if (Serial.available())
  {
      char c = Serial.read();
      switch(c)
      {
        case 'p':
        case 'P':
        temperatureSensor.pair();
        break;

        case 'x':
        case 'X':
        radio.printDetails();
        break;
      }
  }
#endif
}
