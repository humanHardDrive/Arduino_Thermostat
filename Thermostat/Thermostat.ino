#include "ThermostatStation.h"
#include "MCP23s17.h"
#include <LiquidCrystal.h>
#include <SPI.h>

#define SERIAL_DEBUG

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

//Variables
LiquidCrystal   lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
MCP23s17        IOExpander(IO_EXP_CS_PIN, 0);
ThermoStation   thermostat;

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
#endif

  SPI.begin();
}

void loop()
{
  thermostat.background();
}
