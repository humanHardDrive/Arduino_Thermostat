#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <Sleep_n0m1.h>
#include <SoftwareSerial.h>
#include <Streaming.h>

#include "ThermostatDevice.h"
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
DS3231 Clock;
RTClib RTC;
bool bNeedRealTime = true;
uint32_t nLastTimePoll = 0;

char* sPubAliasList[] =
{
  "CurrentTemp",
  "CurrentMode",
  "" /*The empty string is the end of the array*/
};

char* sSubAliasList[] =
{
  "TargetTemp",
  "TargetMode",
  ""
};

void HandleNetworkStateChange(uint8_t state)
{
  LOG << F("Changed to ") << (int)state;
  /*Handle edge specific cases*/
  switch (state)
  {
    default:
      break;
  }
}

void HandleNetworkState(uint8_t state)
{
  switch (state)
  {

  }
}

void procESPNotify(uint8_t cmd, void* buf)
{
  LOG << F("Recived notification ") << (int)cmd;

  switch (cmd)
  {
    case NETWORK_STATE_CHANGE:
      uint8_t state = ((uint8_t*)buf)[0];
      HandleNetworkStateChange(state);
      break;

    case NETWORK_CHANGE:
      espInterface.sendCommand(SAVE, NULL, 0);
      break;
  }
}

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

      /*Continue processing messages while waiting for the response*/
      if (bMsgReady)
      {
        if (inCmd >= NO_NOTIFY)
        {
          procESPNotify(inCmd, *inBuf);
          bMsgReady = false;
        }
        else if (inCmd != cmd)
        {
          LOG << F("Unexpected response for cmd type ") << inCmd;
          bMsgReady = false;
        }
        /*Reset timer*/
        nStartTime = millis();
      }
    }
  }

  if (!bMsgReady)
  {
    LOG << F("No message returned");
    return false;
  }

  return true;
}

bool InitESPInterface()
{
  uint8_t *buf;

  LOG << F("Resetting ESP interface");
  digitalWrite(ESP_RST_PIN, LOW);
  delay(1);
  digitalWrite(ESP_RST_PIN, HIGH);

  /*Wait at most 10 seconds for the interface to show ready status*/
  uint32_t nStatusStartTime = millis();
  while ((millis() - nStatusStartTime) < 10000 &&
         digitalRead(ESP_ST_PIN))
  {
  }

  if (digitalRead(ESP_ST_PIN))
  {
    LOG << F("Interface didn't show ready status in time");
    return false;
  }

  LOG << F("Query for device name");
  if (waitForESPResponse(GET_DEVICE_NAME, NULL, 0, &buf, 10))
    LOG << F("Interface ") << (char*)buf;
  else
  {
    LOG << F("Failed to get device name");
    return false;
  }

  LOG << F("Query for device version");
  if (waitForESPResponse(VERSION, NULL, 0, &buf, 10))
    LOG << F("v") << ((uint16_t*)buf)[0] << '.' << ((uint16_t*)buf)[1];
  else
  {
    LOG << F("Failed to get device version");
    return false;
  }

  LOG << F("Start network helper");
  espInterface.sendCommand(START_NETWORK_HELPER, NULL, 0);

  LOG << F("Query for network name");
  if (waitForESPResponse(GET_NETWORK_NAME, NULL, 0, &buf, 10))
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
    }
  }
  else
  {
    LOG << F("Failed to get network info");
    return false;
  }

  delay(5);
  espInterface.sendCommand(CLEAR_PUB_LIST, NULL, 0);
  espInterface.sendCommand(CLEAR_SUB_LIST, NULL, 0);

  uint8_t nCount = 0;
  while (*sPubAliasList[nCount])
  {
    PubSubInfo info;
    info.nIndex = nCount;
    memset(info.alias, 0, sizeof(info.alias));
    strcpy(info.alias, sPubAliasList[nCount]);

    espInterface.sendCommand(SET_PUB_ALIAS, &info, sizeof(PubSubInfo));
    nCount++;
  }

  nCount = 0;
  while (*sSubAliasList[nCount])
  {
    PubSubInfo info;
    info.nIndex = nCount;
    memset(info.alias, 0, sizeof(info.alias));
    strcpy(info.alias, sSubAliasList[nCount]);

    espInterface.sendCommand(SET_SUB_ALIAS, &info, sizeof(PubSubInfo));
    nCount++;
  }

  return true;
}

bool InitIOExpander()
{
  return false;
}

bool InitRTC()
{
  DateTime then = RTC.now();
  delay(1500);

  if (RTC.now().unixtime() == then.unixtime())
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
  pinMode(ESP_RST_PIN, OUTPUT);
  pinMode(ESP_ST_PIN, INPUT_PULLUP);

  /*Initialize components*/
  if (!InitESPInterface())
  {
    LOG << F("Failed to init ESP interface");
    while (1);
  }

  if (!InitRTC())
  {
    LOG << F("Failed to init RTC");
    while (1);
  }
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
        LOG << F("Unhandled message rsp from command ") << cmd;
    }
  }

  if (bNeedRealTime && (millis() - nLastTimePoll) > 30000)
  {
    uint32_t* pCurrentTime;
    if (waitForESPResponse(TIME, NULL, 0, &pCurrentTime, 10))
    {
      if (*pCurrentTime)
      {
        LOG << F("Got current time");
        bNeedRealTime = false;
      }
      else
        LOG << F("ESP isn't connected to internet. Can't get time");
    }

    nLastTimePoll = millis();
    if (bNeedRealTime)
      LOG << F("Couldn't get time from ESP interface");
  }
}
