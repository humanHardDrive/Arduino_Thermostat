#include "TempSensor.h"

#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "FM25V10.h"
#include <Sleep_n0m1.h>
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SLEEP_TIME  (2*60*1000UL)
#define AWAKE_TIME  (10*1000UL)

#define REMOTE_REQUEST_TIME   500
#define UNPAIR_TIME           2000

#define APP_NAME  F("REMOTE TEMPERATURE SENSOR")
#define VERSION   F("v0.0")

//#define SERIAL_DEBUG

#define LCD_WIDTH  128
#define LCD_HEIGHT 64

#define TEMP_SENSE_PIN  A0
#define BATT_MON_PIN    A1

#define SCK             13
#define MISO            12
#define MOSI            11

#define RF24_CE_PIN     10
#define RF24_CS_PIN     9
#define MEM_CS_PIN      8

#define RIGHT_BTN_PIN   6
#define LEFT_BTN_PIN    5
#define DOWN_BTN_PIN    4
#define UP_BTN_PIN      3
#define CENTER_BTN_PIN  2

RF24 radio(RF24_CE_PIN, RF24_CS_PIN);
FM25V10 memoryDevice(MEM_CS_PIN);
TempSensor temperatureSensor(TEMP_SENSE_PIN);
Adafruit_SSD1306 lcd(LCD_WIDTH, LCD_HEIGHT, &Wire, -1);
Sleep sleep;

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

  pinMode(CENTER_BTN_PIN, INPUT_PULLUP);
  pinMode(UP_BTN_PIN, INPUT_PULLUP);
  pinMode(DOWN_BTN_PIN, INPUT_PULLUP);
  pinMode(LEFT_BTN_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BTN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CENTER_BTN_PIN), UserBtnHandler, FALLING);

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
