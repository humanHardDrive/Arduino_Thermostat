#ifndef __MENU_H__
#define __MENU_H__

#include "Arduino.h"

#define TEMP_READING_LINE   0
#define SCHEDULE_LINE       1
#define MODE_LINE           2
#define MODE_OFFSET         0
#define FAN_LINE            2
#define FAN_OFFSET          11
#define TIME_LINE           3
#define DATE_OFFSET         2
#define TIME_OFFSET         (DATE_OFFSET + 7)
#define DAY_OFFSET          (DATE_OFFSET + 14)

#define SCHEDULE_STRING         F("Schedule: ")
#define SET_TEMP_STRING         F("Set: ")
#define MODE_STRING             F("Mode: ")
#define HEAT_STRING             F("Heat")
#define COOL_STRING             F("Cool")
#define ON_STRING               F("On")
#define OFF_STRING              F("Off")
#define AUTO_STRING             F("Auto")
#define MENU_STRING             F("Menu")
#define FAN_STRING              F("Fan: ")
#define EXIT_STRING             F("Exit")

#define MONDAY_STRING           F(" M")
#define TUESDAY_STRING          F(" T")
#define WEDNESDAY_STRING        F(" W")
#define THURSDAY_STRING         F("TH")
#define FRIDAY_STRING           F(" F")
#define SATURDAY_STRING         F("SA")
#define SUNDAY_STRING           F("SU")

#define SET_DATE_TIME_STRING    F("Set Date/Time")
#define DISCOVER_DEVICES_STRING F("Discover Devices")
#define SET_SCHEDULE_STRING     F("Set Schedule")

#endif
