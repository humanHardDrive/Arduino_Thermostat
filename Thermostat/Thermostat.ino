#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <Sleep_n0m1.h>
#include <SoftwareSerial.h>

#include "MCP23017.h"
#include "ThermostatStation.h"
#include "Menu.h"

//#define SERIAL_DEBUG

#define STAY_AWAKE
//#define NO_IO_EXP
//#define NO_RTC

#define SLEEP_TIME     (30*1000UL)
#define AWAKE_TIME     (10*1000UL)

#define LCD_ROWS    4
#define LCD_COLS    20

#define APP_NAME    F("REMOTE THERMOSTAT")
#define VERSION     F("v0.0")

//Arduino Pins
#define LCD_RS_PIN      9
#define LCD_EN_PIN      8
#define LCD_D4_PIN      7
#define LCD_D5_PIN      6
#define LCD_D6_PIN      5
#define LCD_D7_PIN      4
#define IO_EXP_INT_PIN  2

#define IO_EXP_CS_PIN   A0
#define IO_EXP_RST_PIN  A1
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
LiquidCrystal   lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
MCP23s17        IOExpander(IO_EXP_CS_PIN, IO_EXP_RST_PIN, 0);
DS3231          rtc;
ThermoStation   thermostat(LOCAL_TEMP_PIN);
Sleep           sleep;

#define IO_DEBOUNCE_TIME  5
uint32_t lastIOExpUpdateTime = 0;
byte buttonFilter[IO_DEBOUNCE_TIME], currentBtnState = 0xFF, oldBtnState = 0xFF;
char btnEdge[ALL_BTNS];
byte outputMirror = 0x00;

bool bOldHeatState = false, bOldCoolState = false, bOldFanState = false;

bool bAwake = true;
volatile uint32_t nTimeAwake = 0;

bool ScheduleSettingsFn();
bool DateTimeSettingsFn();
bool ResetDeviceSettingsFn();
bool AboutSettingsFn();

char blankLine[LCD_COLS + 1]; //Array used to clear a specific line
bool bInSettings = false, bForceLCDUpdate = true;
bool (*settingsFn)(void) = NULL;
uint8_t nSettingsCursorPos = 0;

uint8_t RTCHour()
{
  bool b1, b2;
  return rtc.getHour(b1, b2);
}

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

void InitRTC()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Check RTC"));
  uint8_t nSecond;
  nSecond = rtc.getSecond();
  delay(2000); //Wait at least 1 second
  lcd.setCursor(0, 1);
  if (nSecond != rtc.getSecond())
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

  thermostat.background(rtc.getDoW(), RTCHour(), rtc.getMinute()); //Call one iteration of the backround loop to get the target temp
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

#ifndef NO_RTC
  InitRTC();
#endif

  sleep.pwrDownMode();
  InitThermostat();
  lcd.clear();
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
    outputMirror |= (byte)((1 << LCD_BACKLIGHT)); //Turn off the backlight
    UpdateControlOutputs(); //Update the IO expander outputs

    //Reset the menu selection when going to sleep
    nSelectedColumn = -1;
    nSelectedRow = -1;

    bAwake = false;
    sleep.sleepDelay(SLEEP_TIME, bAwake);
    bAwake = true;
    nTimeAwake = millis();
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
      InitIOExpander(false);

    UpdateButtonStates();
    UpdateControlOutputs();
    lastIOExpUpdateTime = millis();
  }
}

//Menu functions
void PrintDayOfWeek(uint8_t day)
{
  switch (day)
  {
    case ThermoStation::SUNDAY:
      lcd.print(SUNDAY_STRING);
      break;

    case ThermoStation::MONDAY:
      lcd.print(MONDAY_STRING);
      break;

    case ThermoStation::TUESDAY:
      lcd.print(TUESDAY_STRING);
      break;

    case ThermoStation::WEDNESDAY:
      lcd.print(WEDNESDAY_STRING);
      break;

    case ThermoStation::THURSDAY:
      lcd.print(THURSDAY_STRING);
      break;

    case ThermoStation::FRIDAY:
      lcd.print(FRIDAY_STRING);
      break;

    case ThermoStation::SATURDAY:
      lcd.print(SATURDAY_STRING);
      break;
  }
}

void PrintTimeOfDay(uint8_t nHour, uint8_t nMinute, bool b24hour)
{
  if (nHour < 10)
    lcd.print(0);
  lcd.print(nHour);

  lcd.print(':');

  if (nMinute < 10)
    lcd.print(0);
  lcd.print(nMinute);
}

void HandleThermostatControlInput()
{
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
    switch (thermostat.getHeatMode())
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
    switch (thermostat.getFanMode())
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
    bInSettings = true;
    bForceLCDUpdate = true;
  }
}

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

void UpdateTimeMenuItem(bool force)
{
  static uint8_t oldRTCMinute = 0;

  //Only need to update on the minute mark
  if (force || oldRTCMinute != rtc.getMinute())
  {
    lcd.setCursor(0, 3);
    lcd.print(blankLine);

    lcd.setCursor(2, 3);
    PrintDayOfWeek(rtc.getDoW());

    lcd.setCursor(13, 3);
    PrintTimeOfDay(RTCHour(), rtc.getMinute(), true);

    oldRTCMinute = rtc.getMinute();
  }
}

void UpdateThermostatMenu(bool force)
{
  //Reset the force flag
  bForceLCDUpdate = false;

  //Handle inputs
  HandleThermostatControlInput();

  //Draw the menu items
  UpdateScheduleMenuItem(force);
  UpdateModeandFanMenuItem(force);
  UpdateTimeMenuItem(force);
}

//Settings functions
bool ScheduleSettingsFn()
{
  return true;
}

bool DateTimeSettingsFn()
{
  static bool bFirstCall = true;
  static uint8_t nDayOfWeek, nHour, nMinute;
  static uint8_t nSelectedPos;

  if (bFirstCall)
  {
    bool b1, b2;
    nDayOfWeek = rtc.getDoW();

    nHour = RTCHour();
    nMinute = rtc.getMinute();
    
    lcd.clear();

    lcd.setCursor(2, 0);
    PrintDayOfWeek(nDayOfWeek);

    lcd.setCursor(13, 0);
    PrintTimeOfDay(nHour, nMinute, true);

    lcd.setCursor(3, 0);
    lcd.blink();

    bFirstCall = false;
  }

  if (btnEdge[TOGGLE_MODE_BTN] == 1)
  {
    nSelectedPos--;
    if (nSelectedPos > 2)
      nSelectedPos = 2;

    switch (nSelectedPos)
    {
      case 0: //Day
        lcd.setCursor(3, 0);
        break;

      case 1: //Hour
        lcd.setCursor(14, 0);
        break;

      case 2: //Minute
        lcd.setCursor(17, 0);
        break;
    }
  }

  if (btnEdge[TOGGLE_FAN_BTN] == 1)
  {
    nSelectedPos++;
    if (nSelectedPos > 2)
      nSelectedPos = 0;

    switch (nSelectedPos)
    {
      case 0: //Day
        lcd.setCursor(3, 0);
        break;

      case 1: //Hour
        lcd.setCursor(14, 0);
        break;

      case 2: //Minute
        lcd.setCursor(17, 0);
        break;
    }
  }

  if (btnEdge[UP_TEMP_BTN] == 1)
  {
    switch (nSelectedPos)
    {
      case 0: //Day
        nDayOfWeek++;
        if (nDayOfWeek >= 7) //Greater than saturday?
          nDayOfWeek = 0; //Back to sunday

        lcd.setCursor(2, 0);
        PrintDayOfWeek(nDayOfWeek);
        lcd.setCursor(3, 0); //Put the cursor back where it was
        break;

      case 1: //Hour
        nHour++;
        if (nHour >= 24)
          nHour = 0;

        lcd.setCursor(13, 0);
        PrintTimeOfDay(nHour, nMinute, true);
        lcd.setCursor(14, 0);
        break;

      case 2: //Minute
        nMinute++;
        if (nMinute >= 60)
          nMinute = 0;

        lcd.setCursor(13, 0);
        PrintTimeOfDay(nHour, nMinute, true);
        lcd.setCursor(17, 0);
        break;
    }
  }

  if (btnEdge[DOWN_TEMP_BTN] == 1)
  {
    switch (nSelectedPos)
    {
      case 0: //Day
        nDayOfWeek--;
        if (nDayOfWeek >= 7) //Less than sunday?
          nDayOfWeek = 6; //Back to saturday

        lcd.setCursor(2, 0);
        PrintDayOfWeek(nDayOfWeek);
        lcd.setCursor(3, 0); //Put the cursor back where it was
        break;

      case 1: //Hour
        nHour--;
        if (nHour >= 24)
          nHour = 23;

        lcd.setCursor(13, 0);
        PrintTimeOfDay(nHour, nMinute, true);
        lcd.setCursor(14, 0);
        break;

      case 2: //Minute
        nMinute--;
        if (nMinute >= 60)
          nMinute = 59;

        lcd.setCursor(13, 0);
        PrintTimeOfDay(nHour, nMinute, true);
        lcd.setCursor(17, 0);
        break;        
    }
  }

  if (btnEdge[SETTINGS_BTN] == 1)
  {
    rtc.setDoW(nDayOfWeek);
    rtc.setHour(nHour);
    rtc.setMinute(nMinute);
    rtc.setSecond(0);
    
    lcd.noBlink();
    bFirstCall = true;
    return true;
  }

  return false;
}

bool ResetDeviceSettingsFn()
{
  return true;
}

bool AboutSettingsFn()
{
  static bool bFirstCall = true;

  if (bFirstCall)
  {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(APP_NAME);

    lcd.setCursor(0, 1);
    lcd.print(VERSION);
    bFirstCall = false;
  }

  for (uint8_t i = 0; i < ALL_BTNS; i++)
  {
    if (btnEdge[i] == 1)
    {
      bFirstCall = true;
      return true;
    }
  }

  return false;
}

void HandleSettingsInput()
{
  if (btnEdge[UP_TEMP_BTN] == 1)
  {
    //Because moving down is increasing pos
    if (nSettingsCursorPos > 0)
      nSettingsCursorPos--;
  }

  if (btnEdge[DOWN_TEMP_BTN] == 1)
  {
    //And moving up is decreasing pos
    if (nSettingsCursorPos < (ALL_SETTINGS - 1))
      nSettingsCursorPos++;
  }

  if (btnEdge[TOGGLE_MODE_BTN] == 1)
  {
  }

  if (btnEdge[TOGGLE_FAN_BTN] == 1)
  {
  }

  if (btnEdge[SETTINGS_BTN] == 1)
  {
    bInSettings = false;
    bForceLCDUpdate = true;
    nSettingsCursorPos = 0;
  }
}

void DrawSettingsList(bool force)
{
  static uint8_t nOldCursorPos = 0;
  uint8_t nCurrentPage, nOldPage, nBaseIndex;
  char sBuffer[LCD_COLS];

  nCurrentPage = nSettingsCursorPos / LCD_ROWS;
  nOldPage = nOldCursorPos / LCD_ROWS;
  nBaseIndex = nCurrentPage * LCD_ROWS;

  if (force || nCurrentPage != nOldPage)
  {
    //Redraw everything
    for (uint8_t i = 0; i < LCD_ROWS; i++)
    {
      lcd.setCursor(0, i);
      lcd.print(blankLine);

      if ((nBaseIndex + i) < ALL_SETTINGS)
      {
        lcd.setCursor(0, i);
        strcpy_P(sBuffer, (char*)pgm_read_word(&SETTING_STRING_TABLE[nBaseIndex + i]));
        if (i == (nSettingsCursorPos % LCD_ROWS))
          lcd.print('>');

        lcd.print(sBuffer);
      }
    }
  }
  else if (nOldCursorPos != nSettingsCursorPos)
  {
    uint8_t modPos;
    //Only redraw what's changed
    //Redraw the old selection
    modPos = nOldCursorPos % LCD_ROWS;
    lcd.setCursor(0, modPos);
    lcd.print(blankLine);
    strcpy_P(sBuffer, (char*)pgm_read_word(&SETTING_STRING_TABLE[nBaseIndex + modPos]));
    lcd.setCursor(0, modPos);
    lcd.print(sBuffer);

    //Draw the new
    modPos = nSettingsCursorPos % LCD_ROWS;
    lcd.setCursor(0, modPos);
    lcd.print(blankLine);
    strcpy_P(sBuffer, (char*)pgm_read_word(&SETTING_STRING_TABLE[nBaseIndex + modPos]));
    lcd.setCursor(0, modPos);
    lcd.print('>');
    lcd.print(sBuffer);
  }

  nOldCursorPos = nSettingsCursorPos;
}

void UpdateSettingsMenu(bool force)
{
  //Reset the force flag
  bForceLCDUpdate = false;

  if (!settingsFn)
  {
    HandleSettingsInput();

    DrawSettingsList(force);
  }
  else
  {
    if (settingsFn())
    {
      bForceLCDUpdate = true;
      settingsFn = NULL;
    }
  }
}

void loop()
{
  bool b1, b2;
  
  UpdateSleepState();
  UpdateIOExpander();

  if (!bInSettings)
    UpdateThermostatMenu(bForceLCDUpdate);
  else
    UpdateSettingsMenu(bForceLCDUpdate);

  //Update the thermostat with the current time
  thermostat.background(rtc.getDoW(), rtc.getHour(b1, b2), rtc.getMinute());

  //Clear button inputs
  memset(btnEdge, 0, sizeof(btnEdge));
}
