#ifndef __MENU_H__
#define __MENU_H__

#include <avr/pgmspace.h>

const char SET_TEMP_STRING[] PROGMEM = "Set: ";
const char HEAT_STRING[] PROGMEM = "Heat";
const char COOL_STRING[] PROGMEM = "Cool";
const char ON_STRING[] PROGMEM = "On";
const char OFF_STRING[] PROGMEM = "Off";
const char AUTO_STRING[] PROGMEM = "Auto";
const char MENU_STRING[] PROGMEM = "Menu";
const char FAN_STRING[] PROGMEM = "Fan: ";

const char DISCOVER_DEVICES_STRING[] PROGMEM = "Discover Devices";

const char* const string_table[] PROGMEM = 
{
};

#endif
