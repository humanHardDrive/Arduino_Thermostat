#include <PubSubClient.h>

#include "SerialInterface.h"

#define MAX_NAME_LENGTH 32

void* MemBlock[16];

struct SAVE_INFO
{
  char sNetworkName[MAX_NAME_LENGTH];
  char sNetworkPass[MAX_NAME_LENGTH];

  char sServerName[MAX_NAME_LENGTH];
  char sServerPass[MAX_NAME_LENGTH];

  uint32_t checksum;
};

SAVE_INFO SavedInfo;
SerialInterface serInterface;

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  if(Serial.available())
    serInterface.update(Serial.read());
}
