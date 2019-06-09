#ifndef __MENU_H__
#define __MENU_H__

#include <avr/pgmspace.h>

#define SCHEDULE_STRING         F("Schedule: ")
#define SET_TEMP_STRING         F("Set: ")
#define MODE_STRING             F("Mode: ")
#define HEAT_STRING             F("Heat")
#define COOL_STRING             F("Cool")
#define ON_STRING               F("On  ")
#define OFF_STRING              F("Off ")
#define AUTO_STRING             F("Auto")
#define MENU_STRING             F("Menu")
#define FAN_STRING              F("Fan: ")
#define SETTINGS_STRING         F("Settings")

#define MONDAY_STRING           F(" M")
#define TUESDAY_STRING          F(" T")
#define WEDNESDAY_STRING        F(" W")
#define THURSDAY_STRING         F("TH")
#define FRIDAY_STRING           F(" F")
#define SATURDAY_STRING         F("SA")
#define SUNDAY_STRING           F("SU")

#define NUM_SETTING_OPTIONS     7

const char SET_SCHEDULE_STRING[] PROGMEM = "Set Schedule";
const char SET_DATE_TIME_STRING[] PROGMEM = "Set Date/Time";
const char DISCOVER_DEVICES_STRING[] PROGMEM = "Discover Devices";
const char UNPAIR_DEVICE_STRING[] PROGMEM = "Unpair Device";
const char RESET_DEVICE_STRING[] PROGMEM = "Reset Device";
const char ABOUT_STRING[] PROGMEM = "About";
const char EXIT_STRING[] PROGMEM = "Exit";

enum
{
  SET_SCHEDULE_SETTING,
  SET_DATE_TIME_SETTING,
  DISCOVER_DEVICE_SETTING,
  UPAIR_DEVICE_SETTING,
  RESET_DEVICE_SETTING,
  ABOUT_SETTING,
  EXIT_SETTING,
  ALL_SETTINGS
};

static const char *const SETTING_STRING_TABLE[] PROGMEM = 
{
  SET_SCHEDULE_STRING,
  SET_DATE_TIME_STRING,
  DISCOVER_DEVICES_STRING,
  UNPAIR_DEVICE_STRING,
  RESET_DEVICE_STRING,
  ABOUT_STRING,
  EXIT_STRING
};

#define SET_SCHEDULE_OPTION     0
#define SET_SCHEDULE_STRING     F("Set Schedule")

#define SET_DATE_TIME_OPTION    1
#define SET_DATE_TIME_STRING    F("Set Date/Time")

#define DISCOVER_DEVICES_OPTION 2
#define DISCOVER_DEVICES_STRING F("Discover Devices")
#define DISCOVERING_STRING      F("Discovering...")
#define FOUND_STRING            F("Found: ");

#define UNPAIR_DEVICE_OPTION    3
#define UNPAIR_STRING           F("Unpair Device")

#define RESET_OPTION            4
#define RESET_STRING            F("Reset Device")

#define ABOUT_OPTION            5
#define ABOUT_STRING            F("About")

#define EXIT_OPTION             6
#define EXIT_STRING             F("Exit")

#endif
