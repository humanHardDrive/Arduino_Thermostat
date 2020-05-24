#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "SensorDevice.h"

/*Default sleep time is 5 minutes*/
#define DEFAULT_SLEEP_TIME_S  (5*60)
#define DEFAULT_SLEEP_TIME_MS (DEFAULT_SLEEP_TIME_S*1000)
#define DEFAULT_SLEEP_TIME_US (DEFAULT_SLEEP_TIME_MS*1000)
#define WAKE_TIME_S           (10)
#define WAKE_TIME_MS          (WAKE_TIME_S*1000)

#define DEBOUNCE_TIME         15

#define CHARGE_STATUS_PIN     1
#define HB_LED_PIN            2
#define CHARGER_STATUS_PIN    3
#define BATT_LED_PIN          4
#define UP_BTN_PIN            5
#define SCL_PIN               9
#define SDA_PIN               10
#define DOWN_BTN_PIN          12
#define CENTER_BTN_PIN        13
#define BATTERY_STATUS_PIN    14
#define SLEEP_PIN             15

#define TEMP_SENSE_PIN  A0

SensorDevice sensor(TEMP_SENSE_PIN, 100);

uint32_t ulSleepTime = DEFAULT_SLEEP_TIME_US;
uint32_t ulWakeTimeStart = 0;

void setup()
{
  pinMode(UP_BTN_PIN, INPUT_PULLUP);
  pinMode(DOWN_BTN_PIN, INPUT_PULLUP);
  pinMode(CENTER_BTN_PIN, INPUT_PULLUP);

  pinMode(CHARGE_STATUS_PIN, INPUT);
  pinMode(CHARGER_STATUS_PIN, INPUT);
  pinMode(BATTERY_STATUS_PIN, INPUT);

  pinMode(HB_LED_PIN, OUTPUT);
  pinMode(BATT_LED_PIN, OUTPUT);
  pinMode(SLEEP_PIN, OUTPUT);

  digitalWrite(HB_LED_PIN, HIGH);
  digitalWrite(BATT_LED_PIN, LOW);
  digitalWrite(SLEEP_PIN, LOW);

  ulWakeTimeStart = millis();
}

void goToSleep()
{
  //Sleep
  //Setup the reset latch
  digitalWrite(HB_LED_PIN, LOW); //Off
  digitalWrite(SLEEP_PIN, HIGH); //Before on
  //Turn off the battery status LED
  digitalWrite(BATT_LED_PIN, LOW);
  //Turn off WiFi
  WiFi.mode(WIFI_OFF);
  //Deep sleep
  ESP.deepSleep(ulSleepTime, WAKE_RF_DISABLED);

  //Wakeup
  //Clear the reset latch
  digitalWrite(SLEEP_PIN, LOW); //Off
  digitalWrite(HB_LED_PIN, HIGH); //Before on
  ulWakeTimeStart = millis();
}

unsigned long ulLastHBUpdate = 0;
unsigned long ulLastBattUpdate = 0;
void updateStatusLED()
{
  //Charger is on
  if (digitalRead(CHARGER_STATUS_PIN))
  {
    //HB led is always active
    digitalWrite(HB_LED_PIN, HIGH);
    ulLastHBUpdate = millis();

    //Toggle the battery indication LED until charged
    //Battery is charging
    if (!digitalRead(CHARGE_STATUS_PIN))
    {
      //Toggle the battery status LED every 0.5 second while charging
      if ((millis() - ulLastBattUpdate) > 500)
      {
        if (digitalRead(BATT_LED_PIN))
          digitalWrite(BATT_LED_PIN, LOW);
        else
          digitalWrite(BATT_LED_PIN, HIGH);

        ulLastBattUpdate = millis();
      }
    }
    else //Charged
    {
      digitalWrite(BATT_LED_PIN, HIGH);
      ulLastBattUpdate = millis();
    }
  }
  else
  {
    //Toggle the heartbeat LED every 1 second
    if ((millis() - ulLastHBUpdate) > 1000)
    {
      if (digitalRead(HB_LED_PIN))
        digitalWrite(HB_LED_PIN, LOW);
      else
        digitalWrite(HB_LED_PIN, HIGH);

      ulLastHBUpdate = millis();
    }

    //Update the battery indicator LED to show low voltage
    digitalWrite(BATT_LED_PIN, !digitalRead(BATTERY_STATUS_PIN));
  }
}

void loop()
{
  sensor.update();

  updateStatusLED();

  if ((millis() - ulWakeTimeStart) > WAKE_TIME_MS)
    goToSleep();
}
