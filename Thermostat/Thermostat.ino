#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <Sleep_n0m1.h>
#include <SoftwareSerial.h>
#include <Streaming.h>

#include "ESPInterface.h"

#define APP_NAME    F("REMOTE THERMOSTAT")
#define VERSION_MAJOR   0
#define VERSION_MINOR   0

/*Basic logging macro*/
#define LOG logger << "\n\r" << millis() << '\t' << __FUNCTION__ << '\t'

//Arduino Pins
#define IO_EXP_RST_PIN  13
#define ESP_RST_PIN     12
#define ESP_EN_PIN      11
#define ESP_ST_PIN      10
#define LCD_RS_PIN      9
#define LCD_EN_PIN      8
#define LCD_D4_PIN      7
#define LCD_D5_PIN      6
#define LCD_D6_PIN      5
#define LCD_D7_PIN      4
#define HEARTBEAT_PIN   3
#define IO_EXP_INT_PIN  2

#define BATT_MON_EN_PIN A0
#define DBG_TX_PIN      A1
#define DBG_RX_PIN      A2
#define I2C_SDA         A4
#define I2C_SCL         A5
#define LOCAL_TEMP_PIN  A6
#define BATT_MON_PIN    A7

//Variables
SoftwareSerial dbg(DBG_RX_PIN, DBG_TX_PIN);
Stream& logger(dbg);
ESPInterface    espInterface;

bool InitESPInterface()
{
  uint8_t cmd, *buf;
  bool bMsgReady = false;

  espInterface.sendCommand(VERSION, NULL, 0);
  delay(2);
  uint32_t nStartTime = millis();

  while ((millis() - nStartTime) < 10 && !bMsgReady)
  {
    if(Serial.available())
    {
      espInterface.background(Serial.read());
      bMsgReady = espInterface.messageReady(&cmd, &buf);
    }
  }

  if(!bMsgReady)
  {
    LOG << F("No data returned");
    return false;
  }

  if(cmd != VERSION)
  {
    LOG << F("Wrong command returned");
    return false;
  }

  LOG << F("Interface v") << ((uint16_t*)buf)[0] << '.' << ((uint16_t*)buf)[1];

  return true;
}

void setup()
{
  /*Setup serial*/
  Serial.begin(57600);
  dbg.begin(4800);

  /*Setup pin directions*/

  /*Initialize components*/
  if (!InitESPInterface())
  {
    LOG << F("Failed to init ESP interface");
    while (1);
  }
}

void loop()
{

}
