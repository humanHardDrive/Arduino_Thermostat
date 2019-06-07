#ifndef __MENU_H__
#define __MENU_H__

#include "Arduino.h"

typedef struct MENU_ITEM
{
  char cursorRow, cursorCol;
  
  void (*printLabel)(void);
  void (*printField)(void);
  
  MENU_ITEM* nextItem[4];
  bool (*btnFn)(uint8_t btn);
} MENU_ITEM_T;

void Menu_SetupMainMenu();

#define TEMP_READING_LINE     0

#define SCHEDULE_LINE         1
#define SCHEDULE_OFFSET       0
#define SCHEDULE_VAL_OFFSET   10
#define SET_LINE              1
#define SET_OFFSET            15

#define MODE_LINE           2
#define MODE_OFFSET         0
#define MODE_VAL_OFFSET     6
#define FAN_LINE            2
#define FAN_OFFSET          11
#define FAN_VAL_OFFSET      16

#define TIME_LINE           3
#define DATE_OFFSET         2
#define TIME_OFFSET         (DATE_OFFSET + 7)
#define DAY_OFFSET          (DATE_OFFSET + 14)
#define SETTINGS_LINE       3
#define SETTINGS_OFFSET     6

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
