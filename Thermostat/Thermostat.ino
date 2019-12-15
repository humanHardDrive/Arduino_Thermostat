#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <Sleep_n0m1.h>
#include <SoftwareSerial.h>

#include "MCP23017.h"
#include "ESPInterface.h"
#include "ThermostatStation.h"
#include "Menu.h"

#define APP_NAME    F("REMOTE THERMOSTAT")
#define VERSION     F("v0.0")

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

#define I2C_SDA         A4
#define I2C_SCL         A5
#define LOCAL_TEMP_PIN  A6
#define BATT_MON_PIN    A7

//Variables
ESPInterface    espInterface;

void setup()
{
  
}

void loop()
{
  
}
