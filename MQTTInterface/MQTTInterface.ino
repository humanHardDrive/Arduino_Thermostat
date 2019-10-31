#include <SoftwareSerial.h>
#include <PubSubClient.h>

#include "SerialInterface.h"

#define MAX_NAME_LENGTH 32

#define DBG_TX_PIN  14
#define DBG_RX_PIN  15

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
SoftwareSerial dbg(DBG_TX_PIN, DBG_RX_PIN, false, 256);

void* MemBlock[4] = 
{
  SavedInfo.sNetworkName,
  SavedInfo.sNetworkPass,
  SavedInfo.sServerName,
  SavedInfo.sServerPass
};

void writeHandler(uint8_t* buf, uint8_t len)
{ 
  uint8_t index = buf[0];
  memcpy(MemBlock[index], &buf[1], (len - 1));
}

void readHandler(uint8_t* buf, uint8_t len)
{
}

void resetHandler(uint8_t* buf, uint8_t len)
{ 
}

void saveHandler(uint8_t* buf, uint8_t len)
{
}

void setup() 
{
  Serial.begin(115200);

  serInterface.setCommandHandler('W', 'R', writeHandler);
  serInterface.setCommandHandler('R', 'D', readHandler);
  serInterface.setCommandHandler('R', 'S', resetHandler);
  serInterface.setCommandHandler('S', 'V', saveHandler);
}

void loop() 
{
  if(Serial.available())
    serInterface.update(Serial.read());
}
