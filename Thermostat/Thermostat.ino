#include "ThermostatStation.h"
#include "MCP23s17.h"
#include <LiquidCrystal.h>
#include <SPI.h>

#define SERIAL_DEBUG

//Arduino Pins
#define IO_EXP_RST_PIN  A0

#define IO_EXP_CS_PIN   8
#define MEM_CS_PIN      9
#define RF_CS_PIN       10

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
LiquidCrystal   lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
MCP23s17        IOExpander(IO_EXP_CS_PIN, 0);
ThermoStation   thermostat;

uint32_t lastIOExpUpdateTime = 0;
byte tempButtonState = 0xFF, oldButtonState = 0xFF, currentButtonState = 0xFF;

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
#endif

  SPI.begin();

  IOExpander.reset();
  IOExpander.writeReg(MCP23s17::IODIRA, 0xFF);
  IOExpander.writeReg(MCP23s17::GPPUA, 0xFF);
  IOExpander.writeReg(MCP23s17::IODIRB, 0x00);
}

void UpdateIOExpander()
{
  if (millis() - lastIOExpUpdateTime > 5)
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("UPDATING IO EXPANDER"));
#endif

    byte buttonState = IOExpander.readReg(MCP23s17::GPIOA);
    if (buttonState != currentButtonState)
    {
      if (buttonState != tempButtonState)
        tempButtonState = buttonState;
      else
        currentButtonState = buttonState;
    }
  }
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
  UpdateIOExpander();
  HandleButtonPress();

  thermostat.background();
}
