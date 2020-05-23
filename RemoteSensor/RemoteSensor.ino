#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "SensorDevice.h"

/*Default sleep time is 5 minutes*/
#define DEFAULT_SLEEP_TIME_S  (5*60)
#define DEFAULT_SLEEP_TIME_MS (DEFAULT_SLEEP_TIME_S*1000)
#define DEFAULT_SLEEP_TIME_US (DEFAULT_SLEEP_TIME_MS*1000)
#define WAKE_TIME_S           (10)
#define WAKE_TIME_MS          (WAKE_TIME_S*1000)

#define CHARGE_SATUS_PIN    1
#define HB_LED_PIN          2
#define CHARGER_STATUS_PIN  3
#define BATT_LED_PIN        4
#define UP_BTN_PIN          5
#define SCL_PIN             9
#define SDA_PIN             10
#define DOWN_BTN_PIN        12
#define CENTER_BTN_PIN      13
#define BATTERY_STATUS_PIN  14

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
  pinMode(CENTER_BTN_PIN, INPUT_PULLUP);

  pinMode(SLEEP_PIN, OUTPUT);
  pinMode(WAKE_PIN, OUTPUT);

  digitalWrite(SLEEP_PIN, LOW);
  digitalWrite(SLEEP_PIN, HIGH);
  
  ulWakeTimeStart = millis();
}

void goToSleep()
{
  //Sleep
  //Setup the reset latch
  digitalWrite(WAKE_PIN, LOW); //Off
  digitalWrite(SLEEP_PIN, HIGH); //Before on
  //Turn off WiFi
  WiFi.mode(WIFI_OFF);
  //Deep sleep
  ESP.deepSleep(ulSleepTime, WAKE_RF_DISABLED); 
  
  //Wakeup
  //Clear the reset latch
  digitalWrite(SLEEP_PIN, LOW); //Off
  digitalWrite(WAKE_PIN, HIGH); //Before on
  ulWakeTimeStart = millis();
}

void loop()
{
  sensor.update();
  if((millis() - ulWakeTimeStart) > WAKE_TIME_MS)
    goToSleep();
}
