#include "TempSensor.h"

#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "FM25V10.h"
#include <Sleep_n0m1.h>

#include <SPI.h>

#define SLEEP_TIME  (2*60*1000UL)
#define AWAKE_TIME  (5*1000UL)

#define APP_NAME  F("REMOTE TEMPERATURE SENSOR")
#define VERSION   F("v0.0")

#define SERIAL_DEBUG

#define RF24_CS_PIN   10
#define RF24_CE_PIN   9
#define MEM_CS_PIN    8

#define USER_BTN_PIN  2

RF24 radio(RF24_CE_PIN, RF24_CS_PIN);
FM25V10 memoryDevice(MEM_CS_PIN);
TempSensor temperatureSensor;
Sleep sleep;

uint32_t nUserBtnPressedTime = 0;
volatile uint32_t nTimeAwake = 0;
bool bAwake = false;

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

  //Start the sensor object
  temperatureSensor.addRadio(&radio);
  temperatureSensor.begin();

  pinMode(USER_BTN_PIN, INPUT_PULLUP);

  sleep.pwrDownMode();

#ifdef SERIAL_DEBUG
  radio.printDetails();
  Serial.println();
#endif
}

void updateSleepState()
{
  if ((millis() - nTimeAwake) > AWAKE_TIME)
  {
    bAwake = false;
    radio.powerDown(); //Put the radio to sleep

    //Sleep for the alotted time
    sleep.sleepDelay(SLEEP_TIME, bAwake);

    //Wake everything back up
    nTimeAwake = millis();
    radio.powerUp();
  }
}

void loop()
{
  updateSleepState();
  temperatureSensor.background();

#ifdef SERIAL_DEBUG
  if (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
      case 'p':
      case 'P':
        temperatureSensor.reset(false);
        temperatureSensor.pair(300);
        break;

      case 'x':
      case 'X':
        radio.printDetails();
        break;
    }
  }
#endif
}
