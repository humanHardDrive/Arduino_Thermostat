#include "TempSensor.h"

#include "nRF24L01.h"
#include "RF24.h"

#include <SPI.h>

#define SERIAL_DEBUG

#define RF24_CS_PIN   10
#define RF24_CE_PIN   9

RF24 radio(RF24_CE_PIN, RF24_CS_PIN);
TempSensor temperatureSensor(&radio);

void setup() {
  // put your setup code here, to run once:

}

void loop()
{
  temperatureSensor.background();
}
