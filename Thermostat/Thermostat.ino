#include "ThermostatStation.h"
#include "MCP23s17.h"
#include <LiquidCrystal.h>
#include <DS3231.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#include <Wire.h>
#include <SPI.h>

#define APP_NAME    F("ARDUINO THERMOSTAT")
#define VERSION     F("v0.0")

//Arduino Pins
#define IO_EXP_RST_PIN  A0

#define IO_EXP_CS_PIN   8
#define RF24_CE_PIN     9
#define RF24_CS_PIN     10

#define SPI_MOSI_PIN    11
#define SPI_MISO_PIN    12
#define SPI_SCK_PIN     13

#define LCD_RS_PIN      7
#define LCD_EN_PIN      6
#define LCD_D4_PIN      5
#define LCD_D5_PIN      4
#define LCD_D6_PIN      3
#define LCD_D7_PIN      2

//IO Expander Pins
enum BUTTON_INDEX
{
  UP_BTN = 0,
  DOWN_BTN,
  LEFT_BTN,
  RIGHT_BTN,
  OK_BTN,
  ALL_BTNS
};

//Variables
#pragma GCC push_options
#pragma GCC optimize ("O0")
RF24            radio(RF24_CE_PIN, RF24_CS_PIN);
LiquidCrystal   lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
MCP23s17        IOExpander(IO_EXP_CS_PIN, 0);
RTClib          rtc;
ThermoStation   thermostat;
#pragma GCC pop_options

uint32_t lastIOExpUpdateTime = 0;
byte tempButtonState = 0xFF, oldButtonState = 0xFF, currentButtonState = 0xFF;

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
  printf_begin();
  Serial.println(APP_NAME);
  Serial.println(VERSION);
#endif

  SPI.begin();
  Wire.begin();

  //Init the IO expander
  IOExpander.reset();
  IOExpander.writeReg(MCP23s17::IODIRA, 0xFF);
  IOExpander.writeReg(MCP23s17::GPPUA, 0xFF);
  IOExpander.writeReg(MCP23s17::IODIRB, 0x00);

  //Check the radio
  if (!radio.isChipConnected())
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to connect to radio..."));
#endif
    while (1);
  }

  //Start the thermostat object
  thermostat.addRadio(&radio);
  thermostat.begin();

#ifdef SERIAL_DEBUG
  radio.printDetails();

  Serial.println();
#endif
}

void HandleButtonPress()
{
  for (byte i = 0; i < ALL_BTNS; i++)
  {
    char d = 0;

    if ((currentButtonState & (1 << i)) != (oldButtonState & (1 << i)))
    {
      if ((currentButtonState & (1 << i)))
        d = -1; //Release
      else
        d = 1; //Press
    }
  }

  oldButtonState = currentButtonState;
}

bool bOldHeatState = false, bOldCoolState = false, bOldFanState = false;

void loop()
{
  HandleButtonPress();

  thermostat.background(rtc.now());

  if (thermostat.isHeatOn() && !bOldHeatState)
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("HEAT ON"));
#endif
  }
  else if (!thermostat.isHeatOn() && bOldHeatState)
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("HEAT OFF"));
#endif
  }

  if (thermostat.isCoolOn() && !bOldCoolState)
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("COOL ON"));
#endif
  }
  else if (!thermostat.isCoolOn() && bOldCoolState)
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("COOL OFF"));
#endif
  }

  if (thermostat.isFanOn() && !bOldFanState)
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("FAN ON"));
#endif
  }
  else if (!thermostat.isFanOn() && bOldFanState)
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("FAN OFF"));
#endif
  }

  bOldHeatState = thermostat.isHeatOn();
  bOldCoolState = thermostat.isCoolOn();
  bOldFanState = thermostat.isFanOn();

#ifdef SERIAL_DEBUG
  if (Serial.available())
  {
    char c = Serial.read();
    switch(c)
    {
      case 'd':
      case 'D':
      thermostat.startDiscovery(5000);
      break;

      case 's':
      case 'S':
      thermostat.stopDiscovery();
      break;

      case 'x':
      case 'X':
      radio.printDetails();
      break;
    }
  }
#endif
}
