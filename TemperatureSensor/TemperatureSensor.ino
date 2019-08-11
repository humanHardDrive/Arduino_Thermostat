#include "TempSensor.h"

#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "FM25V10.h"
#include <Sleep_n0m1.h>
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#define NO_SLEEP
#define SLEEP_TIME  (30*1000UL)
//#define SLEEP_TIME  (2*60*1000UL)
#define AWAKE_TIME  (10*1000UL)

#define REMOTE_REQUEST_TIME   500
#define UNPAIR_TIME           2000

#define APP_NAME  F("REMOTE TEMPERATURE SENSOR")
#define VERSION   F("v0.0")

#define DEBOUNCE_TIME   10

#define NO_RADIO
#define NO_MEMORY
#define NO_LCD
#define SERIAL_DEBUG

#define LCD_WIDTH  128
#define LCD_HEIGHT 32

#define TEMP_SENSE_PIN  A0
#define BATT_MON_PIN    A1

#define SCK             13
#define MISO            12
#define MOSI            11

#define RF24_CE_PIN     10
#define RF24_CS_PIN     9
#define MEM_CS_PIN      8

#define RIGHT_BTN_PIN   6
#define LEFT_BTN_PIN    5
#define DOWN_BTN_PIN    4
#define UP_BTN_PIN      3
#define CENTER_BTN_PIN  2

RF24 radio(RF24_CE_PIN, RF24_CS_PIN);
FM25V10 memoryDevice(MEM_CS_PIN);
TempSensor temperatureSensor(TEMP_SENSE_PIN);
Adafruit_SSD1306 lcd(LCD_WIDTH, LCD_HEIGHT, &Wire, -1);
Sleep sleep;

volatile uint32_t nTimeAwake = 0;
bool bAwake = false, bUser = false;

uint8_t btnStateArray[DEBOUNCE_TIME];

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
  printf_begin();
  Serial.println(APP_NAME);
  Serial.println(VERSION);
  Serial.println();
#endif

  SPI.begin();

#ifndef NO_RADIO
  if (!radio.isChipConnected())
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to connect to radio..."));
#endif
    while (1);
  }
#endif

  memset(btnStateArray, 0, sizeof(btnStateArray));

  //Start the sensor object
  temperatureSensor.addRadio(&radio);
  temperatureSensor.begin();

  pinMode(CENTER_BTN_PIN, INPUT_PULLUP);
  pinMode(UP_BTN_PIN, INPUT_PULLUP);
  pinMode(DOWN_BTN_PIN, INPUT_PULLUP);
  pinMode(LEFT_BTN_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BTN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CENTER_BTN_PIN), CenterBtnHandler, FALLING);

  if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("Failed to allocated VBUF..."));
#endif
    while (1);
  }
  lcd.clearDisplay();
  lcd.setTextSize(1);      // Normal 1:1 pixel scale
  lcd.setTextColor(WHITE); // Draw white text
  lcd.setCursor(0, 0);     // Start at top-left corner
  lcd.cp437(true);         // Use full 256 char 'Code Page 437' font

  sleep.pwrDownMode();

#ifdef SERIAL_DEBUG
  radio.printDetails();
  Serial.println();
#endif
}

void UpdateBtnState()
{
  for (uint8_t i = 0; i < DEBOUNCE_TIME - 1; i++)
    btnStateArray[i + 1] = btnStateArray[i];

  btnStateArray[0] = (PIND & 0x7C) >> 2;
  uint8_t mixedBits = btnStateArray[0];

  for (uint8_t i = 1; i < DEBOUNCE_TIME; i++)
  {
    mixedBits ^= btnStateArray[i];
    mixedBits = ~mixedBits;
  }
}

void sysSleep()
{
  bAwake = false;
  radio.powerDown(); //Put the radio to sleep
  lcd.ssd1306_command(SSD1306_DISPLAYOFF);

  //Sleep for the alotted time
  sleep.sleepDelay(SLEEP_TIME, bAwake);
}

void sysWake(bool bUser)
{
  //Wake everything back up
  nTimeAwake = millis();
  radio.powerUp();
  bAwake = true;

  lcd.clearDisplay();
  UpdateTemperatureDisplay();

  if (bUser)
    lcd.ssd1306_command(SSD1306_DISPLAYON);
}

void CenterBtnHandler()
{
  bAwake = true;
  bUser = true;
}

void UpdateTemperatureDisplay()
{
  lcd.setTextSize(3);
  lcd.setCursor(0, 0);
  lcd.print(temperatureSensor.GetTemperature());
  lcd.write(223);
}

void updateSleepState()
{
  //Stay awake while pairing
  if (temperatureSensor.isPairing())
    nTimeAwake = millis();

  if ((millis() - nTimeAwake) > AWAKE_TIME)
  {
#ifdef SERIAL_DEBUG
    Serial.println(F("SLEEP"));
    delay(500);
#endif

    bUser = false;
    sysSleep();
    sysWake(bUser);

#ifdef SERIAL_DEBUG
    Serial.println(F("AWAKE"));
#endif
  }
}

void loop()
{
#ifndef NO_SLEEP
  updateSleepState();
#endif
  temperatureSensor.background();
  lcd.display();

#ifdef SERIAL_DEBUG
  if (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
      case 'p':
      case 'P':
        temperatureSensor.reset(false);
        temperatureSensor.pair(300);
        break;

      case 'x':
      case 'X':
        radio.printDetails();
        break;
    }
  }
#endif
}
