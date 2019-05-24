#include "MCP23s17.h"
#include <LiquidCrystal.h>
#include <DS3231.h>
#include "ThermostatStation.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "Menu.h"

#define NO_RADIO
//#define NO_IO_EXP
#define NO_RTC
#define NO_STORAGE

#include <Wire.h>
#include <SPI.h>

#define APP_NAME    F("SMART THERMOSTAT")
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
RF24            radio(RF24_CE_PIN, RF24_CS_PIN);
LiquidCrystal   lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
MCP23s17        IOExpander(IO_EXP_CS_PIN, 0);
RTClib          rtc;
ThermoStation   thermostat;

uint32_t lastIOExpUpdateTime = 0;
byte tempButtonState = 0xFF, oldButtonState = 0xFF, currentButtonState = 0xFF;

bool bOldHeatState = false, bOldCoolState = false, bOldFanState = false, bForceUpdate = false;
uint32_t nLastTempUpdate = 0;

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
  Serial.println(APP_NAME);
  Serial.println(VERSION);
#endif

  SPI.begin();
  Wire.begin();

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println(APP_NAME);
  lcd.setCursor(0, 1);
  lcd.print(VERSION);
  delay(1000);

#ifndef NO_IO_EXP
  //Init the IO expander
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Init IO expander"));
  IOExpander.reset();
  IOExpander.writeReg(MCP23s17::IODIRA, 0xFF);
  IOExpander.writeReg(MCP23s17::GPPUA, 0xFF);
  IOExpander.writeReg(MCP23s17::IODIRB, 0x00);
  delay(500);
  lcd.setCursor(0, 1);
  if (IOExpander.readReg(MCP23s17::IODIRB) == 0x00 &&
      IOExpander.readReg(MCP23s17::GPPUA) == 0xFF)
    lcd.print(F("SUCCESS"));
  else
  {
    lcd.print(F("FAILED"));
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to initialize IO expander..."));
#endif
    while (1);
  }
  delay(1000);
#endif

#ifndef NO_RADIO
  //Check the radio
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Check radio"));
  lcd.setCursor(0, 1);
  if (!radio.isChipConnected())
  {
    lcd.print(F("FAILED"));
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to connect to radio..."));
#endif
    while (1);
  }
  delay(500);
  lcd.print(F("SUCCESS"));
  delay(1000);
#endif

#ifndef NO_RTC
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Check RTC"));
  DateTime now;
  now = rtc.now();
  delay(2000); //Wait at least 1 second
  lcd.setCursor(0, 1);
  if (now.unixtime() != rtc.now().unixtime())
  {
    lcd.print(F("SUCCESS"));
    delay(1000);
  }
  else
  {
    lcd.print(F("FAILED"));
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to see RTC time change..."));
#endif
    while (1);
  }
#endif

  //Start the thermostat object
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Start thermostat"));
  thermostat.addRadio(&radio);
  thermostat.begin();
  thermostat.background(rtc.now()); //Call one iteration of the backround loop to get the target temp
  lcd.setCursor(0, 1);
  lcd.print(thermostat.getPairedCount());
  lcd.print(F(" paired"));
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(SET_TEMP_STRING);
  lcd.print(thermostat.getTargetTemp());
  lcd.setCursor(0, 1);
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

  if ((millis() - nLastTempUpdate) > 1000)
  {
    nLastTempUpdate = millis();
  }

  bOldHeatState = thermostat.isHeatOn();
  bOldCoolState = thermostat.isCoolOn();
  bOldFanState = thermostat.isFanOn();

#ifdef SERIAL_DEBUG
  uint32_t UID;
  char sName[REMOTE_NAME_LENGTH];

  if (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
      case 'd':
      case 'D':
        thermostat.startDiscovery(5000);
        break;

      case 's':
      case 'S':
        thermostat.stopDiscovery();
        break;

      case '0':
        thermostat.getDiscoveredDevice(0, &UID, sName);
        if (thermostat.pair(UID, sName, 1000))
          Serial.println(F("SUCCESS"));
        else
          Serial.println(F("FAILED"));
        break;

      case 'q':
      case 'Q':
        break;
    }
  }
#endif
}
