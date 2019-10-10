#include <PubSubClient.h>

#define SERIAL_STX  0x55
#define SERIAL_ATX  0xAA

#define MAX_NAME_LENGTH 32

struct SAVE_INFO
{
  char sNetworkName[MAX_NAME_LENGTH];
  char sNetworkPass[MAX_NAME_LENGTH];

  char sServerName[MAX_NAME_LENGTH];
  char sServerPass[MAX_NAME_LENGTH];

  uint32_t checksum;
};

SAVE_INFO SavedInfo;

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
}
