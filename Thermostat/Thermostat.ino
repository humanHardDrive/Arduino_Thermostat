#include "MCP23s17.h"
#include "FM25V10.h"
#include <DS3231.h>
#include "ThermostatStation.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "Menu.h"
#include <LiquidCrystal.h>
#include <Sleep_n0m1.h>

#define NO_RADIO
#define STAY_AWAKE
//#define NO_IO_EXP
//#define NO_RTC
//#define NO_STORAGE
//#define FIRST_BOOT

#define SLEEP_TIME     (30*1000UL)
#define AWAKE_TIME     (10*1000UL)

#include <Wire.h>
#include <SPI.h>

#define LCD_ROWS    4
#define LCD_COLS    20

#define APP_NAME    F("REMOTE THERMOSTAT")
#define VERSION     F("v0.0")

//Arduino Pins
#define SPI_SCK_PIN     13
#define SPI_MISO_PIN    12
#define SPI_MOSI_PIN    11
#define MEM_CS_PIN      10
#define LCD_RS_PIN      9
#define LCD_EN_PIN      8
#define LCD_D4_PIN      7
#define LCD_D5_PIN      6
#define LCD_D6_PIN      5
#define LCD_D7_PIN      4
#define IO_EXP_INT_PIN  2

#define IO_EXP_CS_PIN   A0
#define IO_EXP_RST_PIN  A1
#define RF24_CE_PIN     A2
#define RF24_CS_PIN     A3
#define I2C_SDA         A4
#define I2C_SCL         A5
#define LOCAL_TEMP_PIN  A6

//IO Expander Pins
//Inputs
enum IO_EXP_GPIOA
{
  UP_TEMP_BTN = 0,
  DOWN_TEMP_BTN,
  TOGGLE_MODE_BTN,
  TOGGLE_FAN_BTN,
  SETTINGS_BTN,
  TOGGLE_REMOTE_BTN,
  TOGGLE_SCHEDULE_BTN,
  ALL_BTNS
};

//Outputs
enum IO_EXP_GPIOB
{
  HEAT_ON,
  COOL_ON,
  FAN_ON,
  LCD_BACKLIGHT
};

//Variables
RF24            radio(RF24_CE_PIN, RF24_CS_PIN);
FM25V10         memoryDevice(MEM_CS_PIN);
LiquidCrystal   lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
MCP23s17        IOExpander(IO_EXP_CS_PIN, IO_EXP_RST_PIN, 0);
RTClib          rtc;
ThermoStation   thermostat(LOCAL_TEMP_PIN);
Sleep           sleep;

#define IO_DEBOUNCE_TIME  5
uint32_t lastIOExpUpdateTime = 0;
byte buttonFilter[IO_DEBOUNCE_TIME], currentBtnState = 0xFF, oldBtnState = 0xFF;
char btnEdge[ALL_BTNS];
byte outputMirror = 0x00;

bool bOldHeatState = false, bOldCoolState = false, bOldFanState = false, bForceUpdate = false;
bool bAwake = true, bShowSettings = false, bInSettings = false;
uint32_t nLastLCDUpdate = 0;
volatile uint32_t nTimeAwake = 0;

char blankLine[LCD_COLS + 1]; //Array used to clear a specific line

//Boot functions
void InitLCD()
{
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();
  lcd.setCursor(0, 0);

  memset(blankLine, ' ', sizeof(blankLine)); //Write all spaces
  blankLine[LCD_COLS] = '\0'; //Except the last character to make it a valid string
}

bool IOExpanderGood()
{
  if (IOExpander.readReg(MCP23s17::IODIRB) == 0x00 &&
      IOExpander.readReg(MCP23s17::GPPUA) == 0xFF)
    return true;

  return false;
}

void InitIOExpander(bool post)
{
  if (post)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Init IO expander"));
  }

  IOExpander.reset();
  IOExpander.writeReg(MCP23s17::IODIRA, 0xFF); //Bank A are all inputs
  IOExpander.writeReg(MCP23s17::GPPUA, 0xFF); //Enable pull-ups on bank A
  IOExpander.writeReg(MCP23s17::GPINTENA, 0xFF); //Enable interrupts on all pins
  IOExpander.writeReg(MCP23s17::IODIRB, 0x00); //Bank B are all outputs
  IOExpander.writeReg(MCP23s17::OLATB, outputMirror);

  if (post)
  {
    delay(500);
    lcd.setCursor(0, 1);
    if (IOExpanderGood())
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
  }

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IO_EXP_INT_PIN), IOExpanderIntHandler, FALLING);
}

void InitRadio()
{
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
}

void InitStorage()
{
  byte clearBuffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  byte writeBuffer[8] = {0xDE, 0xAD, 0xBE, 0xEF, 0x11, 0x22, 0xAA, 0xBB};
  byte readBuffer[8];

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Check storage"));
  lcd.setCursor(0, 1);

  memoryDevice.write(0, clearBuffer, 8);
  memoryDevice.read(0, readBuffer, 8);

  if (memcmp(clearBuffer, readBuffer, 8))
  {
    lcd.print(F("FAILED"));
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to verify storage device..."));
#endif
    while (1);
  }

  memoryDevice.write(0, writeBuffer, 8);
  memoryDevice.read(0, readBuffer, 8);

  if (memcmp(writeBuffer, readBuffer, 8))
  {
    lcd.print(F("FAILED"));
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to verify storage device..."));
#endif
    while (1);
  }

  lcd.print(F("SUCCESS"));
  delay(1000);
}

void InitRTC()
{
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
}

void InitThermostat()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Start thermostat"));
  thermostat.addRadio(&radio);
  thermostat.addMemoryDevice(&memoryDevice, 256); //Allocate 256 bytes for non-basestation uses

#ifdef FIRST_BOOT
  thermostat.reset(true);
#endif

  if (!thermostat.recover())
  {
    lcd.setCursor(0, 1);
    lcd.print(F("FAILED"));
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to see RTC time change..."));
#endif
    while (1);
  }

  thermostat.begin();
  thermostat.background(rtc.now()); //Call one iteration of the backround loop to get the target temp
  lcd.setCursor(0, 1);
  lcd.print(thermostat.getPairedCount());
  lcd.print(F(" paired"));
  delay(2000);
}

void IOExpanderIntHandler()
{
#ifdef SERIAL_DEBUG
  Serial.println("INTERRUPT");
#endif

  if (!bAwake)
  {
    outputMirror &= (byte)(~(1 << LCD_BACKLIGHT)); //Turn on the backlight
    UpdateControlOutputs(); //Update the IO expander outputs
  }
  UpdateButtonStates();
  bAwake = true; //Wake up the device
  nTimeAwake = millis();
}

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
  Serial.println(APP_NAME);
  Serial.println(VERSION);
#endif

  memset(buttonFilter, 0xFF, IO_DEBOUNCE_TIME);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV32);

  Wire.begin();

#ifndef NO_IO_EXP
  InitIOExpander(true);
#endif

  InitLCD();

#ifndef NO_RADIO
  InitRadio();
#endif

#ifndef NO_STORAGE
  InitStorage();
#endif

#ifndef NO_RTC
  InitRTC();
#endif

  sleep.pwrDownMode();
  InitThermostat();
  lcd.clear();
  UpdateThermostatMenu(true);
}

void UpdateButtonStates()
{
  byte filteredBtnState;
  currentBtnState = filteredBtnState = IOExpander.readReg(MCP23s17::GPIOA);

  memset(btnEdge, 0, sizeof(btnEdge));

  //Go through the old states and filter the current
  for (byte i = 0; i < IO_DEBOUNCE_TIME; i++)
  {
    filteredBtnState ^= buttonFilter[i]; //Check for the differences
    filteredBtnState = ~filteredBtnState; //Then find the similarities
  }
  //This should filter down to the bits that have stayed the same the last samples

  //Update the previous states
  for (byte i = 1; i < IO_DEBOUNCE_TIME; i++)
    buttonFilter[i] = buttonFilter[i - 1]; //Shift everything back
  buttonFilter[0] = currentBtnState;

  currentBtnState &= filteredBtnState; //Keep the bits that were the same
  currentBtnState |= (oldBtnState & ~filteredBtnState); //Bring back the old bits that didn't change

  for (byte i = 0; i < ALL_BTNS; i++)
  {
    byte mask = (1 << i);
    if ((currentBtnState & mask) != (oldBtnState & mask))
    {
      if (currentBtnState & mask)
        btnEdge[i] = -1;
      else
        btnEdge[i] = 1;
    }
  }

  oldBtnState = currentBtnState;
}

void UpdateThermostatControl()
{
  char btnPressed = -1;

  if (btnEdge[UP_TEMP_BTN] == 1)
  {
    thermostat.setTargetTemp(thermostat.getTargetTemp() + 1);
    thermostat.disableSchedule();
  }

  if (btnEdge[DOWN_TEMP_BTN] == 1)
  {
    thermostat.setTargetTemp(thermostat.getTargetTemp() - 1);
    thermostat.disableSchedule();
  }

  if (btnEdge[TOGGLE_MODE_BTN] == 1)
  {
    switch(thermostat.getHeatMode())
    {
      case ThermoStation::OFF:
      thermostat.setHeatMode(ThermoStation::HEAT);
      break;

      case ThermoStation::HEAT:
      thermostat.setHeatMode(ThermoStation::COOL);
      break;

      case ThermoStation::COOL:
      thermostat.setHeatMode(ThermoStation::OFF);
      break;
    }
  }

  if (btnEdge[TOGGLE_FAN_BTN] == 1)
  {
    switch(thermostat.getFanMode())
    {
      case ThermoStation::ON:
      thermostat.setFanMode(ThermoStation::AUTO);
      break;

      case ThermoStation::AUTO:
      thermostat.setFanMode(ThermoStation::ON);
      break;
    }
  }

  if (btnEdge[SETTINGS_BTN] == 1)
  {

  }
}

//IO Expander Functions
void UpdateControlOutputs()
{
  //Check for changes to the heat control
  if (thermostat.isHeatOn() && !bOldHeatState)
  {
    outputMirror |= (byte)(1 << HEAT_ON);
#ifdef SERIAL_DEBUG
    Serial.println(F("HEAT ON"));
#endif
  }
  else if (!thermostat.isHeatOn() && bOldHeatState)
  {
    outputMirror &= (byte)(~(1 << HEAT_ON));
#ifdef SERIAL_DEBUG
    Serial.println(F("HEAT OFF"));
#endif
  }

  if (thermostat.isCoolOn() && !bOldCoolState)
  {
    outputMirror |= (byte)(1 << COOL_ON);
#ifdef SERIAL_DEBUG
    Serial.println(F("COOL ON"));
#endif
  }
  else if (!thermostat.isCoolOn() && bOldCoolState)
  {
    outputMirror &= (byte)(~(1 << COOL_ON));
#ifdef SERIAL_DEBUG
    Serial.println(F("COOL OFF"));
#endif
  }

  if (thermostat.isFanOn() && !bOldFanState)
  {
    outputMirror |= (byte)(1 << FAN_ON);
#ifdef SERIAL_DEBUG
    Serial.println(F("FAN ON"));
#endif
  }
  else if (!thermostat.isFanOn() && bOldFanState)
  {
    outputMirror &= (byte)(~(1 << FAN_ON));
#ifdef SERIAL_DEBUG
    Serial.println(F("FAN OFF"));
#endif
  }
  //Update the IO expander output
  IOExpander.writeReg(MCP23s17::OLATB, outputMirror);

  bOldHeatState = thermostat.isHeatOn();
  bOldCoolState = thermostat.isCoolOn();
  bOldFanState = thermostat.isFanOn();
}

void UpdateSleepState()
{
#ifndef STAY_AWAKE
  if ((millis() - nTimeAwake) > AWAKE_TIME)
  {
    Serial.println("SLEEP");

    outputMirror |= (byte)((1 << LCD_BACKLIGHT)); //Turn off the backlight
    UpdateControlOutputs(); //Update the IO expander outputs

    //Reset the menu selection when going to sleep
    nSelectedColumn = -1;
    nSelectedRow = -1;
    lcd.noBlink();

    delay(100);

    bAwake = false;
    sleep.sleepDelay(SLEEP_TIME, bAwake);
    bAwake = true;
    nTimeAwake = millis();

    Serial.println("WAKE");
  }
#endif
}

void UpdateIOExpander()
{
  //Update the button states
  if ((millis() - lastIOExpUpdateTime) > 5)
  {
    //Try to re-init the IO expander
    if (!IOExpanderGood())
    {
      Serial.println("BAD IO EXP");
      InitIOExpander(false);
    }

    UpdateButtonStates();
    UpdateControlOutputs();
    UpdateThermostatControl(); //Handle any button presses to update the thermostat
    lastIOExpUpdateTime = millis();
  }
}

//Menu functions
void UpdateScheduleMenuItem(bool force)
{
  static bool bOldScheduleSetting = false;
  static uint8_t nOldTargetTemp = 0;

  if (force || bOldScheduleSetting != thermostat.usingSchedule() || nOldTargetTemp != thermostat.getTargetTemp())
  {
    //Clear the line
    lcd.setCursor(0, 1);
    lcd.print(blankLine);

    lcd.setCursor(0, 1);
    lcd.print(SCHEDULE_STRING);

    if (thermostat.usingSchedule())
      lcd.print(ON_STRING);
    else
      lcd.print(OFF_STRING);

    lcd.setCursor(15, 1);
    lcd.print(thermostat.getTargetTemp());
    lcd.write(223); //Degree symbol

    bOldScheduleSetting = thermostat.usingSchedule();
    nOldTargetTemp = thermostat.getTargetTemp();
  }
}

void UpdateModeandFanMenuItem(bool force)
{
  static uint8_t nOldFanSetting = 0, nOldModeSetting = 0;

  if (force || nOldFanSetting != thermostat.getFanMode() || nOldModeSetting != thermostat.getHeatMode())
  {
    //Clear the line
    lcd.setCursor(0, 2);
    lcd.print(blankLine);

    lcd.setCursor(0, 2);
    lcd.print(MODE_STRING);
    switch (thermostat.getHeatMode())
    {
      case ThermoStation::OFF:
        lcd.print(OFF_STRING);
        break;

      case ThermoStation::HEAT:
        lcd.print(HEAT_STRING);
        break;

      case ThermoStation::COOL:
        lcd.print(COOL_STRING);
        break;
    }

    lcd.setCursor(11, 2);
    lcd.print(FAN_STRING);
    switch (thermostat.getFanMode())
    {
      case ThermoStation::ON:
        lcd.print(ON_STRING);
        break;

      case ThermoStation::AUTO:
        lcd.print(AUTO_STRING);
        break;
    }

    nOldFanSetting = thermostat.getFanMode();
    nOldModeSetting = thermostat.getHeatMode();
  }
}

void UpdateThermostatMenu(bool force)
{
  UpdateScheduleMenuItem(force);
  UpdateModeandFanMenuItem(force);
}

void loop()
{
  UpdateSleepState();
  UpdateIOExpander();
  UpdateThermostatMenu(false);

  //Update the thermostat with the current time
  thermostat.background(rtc.now());
}
