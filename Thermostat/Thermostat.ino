#include "ThermostatStation.h"

#define DISCOVERY_PIN   7

#define DEBOUNCE_TIME   5

ThermoStation thermostat(4,5,6);

void setup() {
  Serial.begin(115200);

  pinMode(DISCOVERY_PIN, INPUT_PULLUP);
}

uint32_t discoveryPinDebounceTime = 0;

void loop() {
  if(!digitalRead(DISCOVERY_PIN))
  {
      if((discoveryPinDebounceTime + DEBOUNCE_TIME) < millis())
        thermostat.startDiscovery(1500);
  }
  else
    discoveryPinDebounceTime = millis();
  
  thermostat.background();
}
