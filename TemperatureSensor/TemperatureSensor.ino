#include "TempSensor.h"

#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "FM25V10.h"
#include <Sleep_n0m1.h>

#include <SPI.h>

#define SLEEP_TIME  (2*60*1000UL)
#define AWAKE_TIME  (10*1000UL)

#define REMOTE_REQUEST_TIME   500
#define UNPAIR_TIME           2000

#define APP_NAME  F("REMOTE TEMPERATURE SENSOR")
#define VERSION   F("v0.0")

#define SERIAL_DEBUG

#define TEMP_SENSE_PIN  A0

#define RF24_CS_PIN     10
#define RF24_CE_PIN     9
#define MEM_CS_PIN      8

#define USER_LED_PIN    4
#define USER_BTN_PIN    2

RF24 radio(RF24_CE_PIN, RF24_CS_PIN);
FM25V10 memoryDevice(MEM_CS_PIN);
TempSensor temperatureSensor(TEMP_SENSE_PIN);
Sleep sleep;

#define LED_PAIR_UPDATE_PERIOD  50

uint32_t nLastUserLEDUpdateTime = 0;
uint8_t nUserLEDValue = 0, nUserLEDChange = 1;

uint32_t nUserBtnPressedTime = 0;
bool bUserBtnState = false;

volatile uint32_t nTimeAwake = 0;
bool bAwake = false;

void UserBtnHandler()
{
  bAwake = true;
  nTimeAwake = millis();
}

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

  pinMode(USER_LED_PIN, OUTPUT);
  digitalWrite(USER_LED_PIN, LOW);

  pinMode(USER_BTN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(USER_BTN_PIN), UserBtnHandler, FALLING);

  sleep.pwrDownMode();

#ifdef SERIAL_DEBUG
  radio.printDetails();
  Serial.println();
#endif
}

void updateSleepState()
{
  //Stay awake while pairing
  if (temperatureSensor.isPairing())
    nTimeAwake = millis();

  if ((millis() - nTimeAwake) > AWAKE_TIME)
  {
    bAwake = false;
    radio.powerDown(); //Put the radio to sleep
    digitalWrite(USER_LED_PIN, LOW); //Turn off the LED

    //Sleep for the alotted time
    sleep.sleepDelay(SLEEP_TIME, bAwake);

    //Wake everything back up
    nTimeAwake = millis();
    radio.powerUp();
  }
}

void updateUserBtn()
{
  //If the button was just pressed
  if (!digitalRead(USER_BTN_PIN) && !bUserBtnState)
  {
    bUserBtnState = true;
    nUserBtnPressedTime = millis();
  }
  else if (digitalRead(USER_BTN_PIN) && bUserBtnState) //The button was released
  {
    if ((millis() - nUserBtnPressedTime) > UNPAIR_TIME)
    {
      //Unpair the device, forget the network
    }
    else if ((millis() - nUserBtnPressedTime) > REMOTE_REQUEST_TIME)
    {
      //Send request to base station to become the remote sensor
    }
  }
}

void updateUserLED()
{
  if (temperatureSensor.isPairing())
  {
    if ((millis() - nLastUserLEDUpdateTime) > LED_PAIR_UPDATE_PERIOD)
    {
      if (!nUserLEDValue)
        nUserLEDChange = 1;
      else
        nUserLEDChange = 255;

      nUserLEDValue += nUserLEDChange;
      analogWrite(USER_LED_PIN, nUserLEDValue);
      nLastUserLEDUpdateTime = millis();
    }
  }
}

void loop()
{
  updateSleepState();
  updateUserBtn();
  updateUserLED();
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
