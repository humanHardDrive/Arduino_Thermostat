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
RTClib RTC;

bool waitForESPResponse(uint8_t cmd, void* outBuf, uint8_t outLen, void** inBuf, uint32_t timeout)
{
  bool bMsgReady = false;
  uint32_t nStartTime;
  uint8_t inCmd;

  espInterface.sendCommand(cmd, outBuf, outLen);
  delay(1);
  nStartTime = millis();

  while ((millis() - nStartTime) < timeout && !bMsgReady)
  {
    if (Serial.available())
    {
      espInterface.background(Serial.read());
      bMsgReady = espInterface.messageReady(&inCmd, inBuf);
    }
  }

  if (!bMsgReady)
  {
    LOG << F("No message returned");
    return false;
  }

  if (inCmd != cmd)
  {
    LOG << F("Wrong type returned");
    return false;
  }

  return true;
}

bool InitESPInterface()
{
  uint8_t *buf;
  bool bRetVal = true;

  if (bRetVal && waitForESPResponse(GET_DEVICE_NAME, NULL, 0, &buf, 10))
    LOG << F("Interface ") << (char*)buf;
  else
  {
    LOG << F("Failed to get device name");
    bRetVal = false;
  }

  if (bRetVal && waitForESPResponse(VERSION, NULL, 0, &buf, 10))
    LOG << F("v") << ((uint16_t*)buf)[0] << '.' << ((uint16_t*)buf)[1];
  else
  {
    LOG << F("Failed to get device version");
    bRetVal = false;
  }

  if (bRetVal && waitForESPResponse(GET_NETWORK_NAME, NULL, 0, &buf, 10))
  {
    if (strlen(buf))
    {
      LOG << F("Connecting to saved network ") << (char*)buf;

      espInterface.sendCommand(CONNECT_TO_AP, NULL, 0);
    }
    else
    {
      LOG << F("No saved network. Start network helper");

      /*Start the AP first*/
      espInterface.sendCommand(START_AP, NULL, 0);
      delay(5);
      /*Then start the network helper*/
      espInterface.sendCommand(START_NETWORK_HELPER, NULL, 0);
    }
  }
  else
  {
    LOG << F("Failed to get network info");
    bRetVal = false;
  }

  return bRetVal;
}

bool InitIOExpander()
{
  return false;
}

bool InitRTC()
{
  DateTime then = RTC.now();
  delay(1500);

  if(RTC.now().unixtime() == then.unixtime())
  {
    LOG << F("Failed to see clock change");
    return false;
  }

  LOG << F("Date ") << then.day() << '/' << then.month() << '/' << then.year();
  LOG << F("Time ") << then.hour() << ':' << then.minute();
  
  return true;
}

void setup()
{
  /*Setup serial*/
  Serial.begin(57600);
  dbg.begin(4800);
  Wire.begin();

  /*Setup pin directions*/

  /*Initialize components*/
  if (!InitESPInterface())
  {
    LOG << F("Failed to init ESP interface");
    while (1);
  }

  if(!InitRTC())
  {
    LOG << F("Failed to init RTC");
    while(1);
  }
}

void procESPNotify(uint8_t cmd, void* buf)
{
  LOG << F("Recived notification ") << (int)cmd;
}

void procESPRsp(uint8_t cmd, void* buf)
{
  LOG << F("Received rsp for cmd ") << (int)cmd;
}

void loop()
{
  uint8_t cmd, *buf;

  if (Serial.available())
  {
    espInterface.background(Serial.read());

    if (espInterface.messageReady(&cmd, &buf))
    {
      if (cmd > NO_NOTIFY)
        procESPNotify(cmd, buf);
      else
        procESPRsp(cmd, buf);
    }
  }
}
