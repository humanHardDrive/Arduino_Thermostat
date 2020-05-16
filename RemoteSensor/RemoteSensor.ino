#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "SensorDevice.h"

/*Default sleep time is 5 minutes*/
#define DEFAULT_SLEEP_TIME_S  (5*60)
#define DEFAULT_SLEEP_TIME_MS (DEFAULT_SLEEP_TIME_S*1000)
#define DEFAULT_SLEEP_TIME_US (DEFAULT_SLEEP_TIME_MS*1000)
#define WAKE_TIME_S           (10)
#define WAKE_TIME_MS          (WAKE_TIME_S*1000)

#define UP_BTN_PIN      0
#define DOWN_BTN_PIN    1
#define LEFT_BTN_PIN    2
#define RIGHT_BTN_PIN   3
#define SLEEP_PIN       4
#define WAKE_PIN        5

#define TEMP_SENSE_PIN  A0

SensorDevice sensor(TEMP_SENSE_PIN, 100);

uint32_t ulSleepTime = DEFAULT_SLEEP_TIME_US;
uint32_t ulWakeTimeStart = 0;

void setup() 
{
  pinMode(UP_BTN_PIN, INPUT_PULLUP);
  pinMode(DOWN_BTN_PIN, INPUT_PULLUP);
  pinMode(LEFT_BTN_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BTN_PIN, INPUT_PULLUP);

  pinMode(SLEEP_PIN, OUTPUT);
  pinMode(WAKE_PIN, OUTPUT);

  digitalWrite(SLEEP_PIN, LOW);
  digitalWrite(SLEEP_PIN, HIGH);
  
  ulWakeTimeStart = millis();
}

void goToSleep()
{
  //Sleep
  WiFi.mode(WIFI_OFF);
  ESP.deepSleep(10, WAKE_RF_DISABLED); 
  //Wakeup
  ulWakeTimeStart = millis();
}

void loop() 
{
  if((millis() - ulWakeTimeStart) > WAKE_TIME_MS)
    goToSleep();
}
