#ifndef __ESPINTERFACE_H__
#define __ESPINTERFACE_H__

#include <Arduino.h>

class ESPInterface
{
  public:
    ESPInterface();
    ~ESPInterface();

    void background(uint8_t c);

    void sendCommand(uint8_t cmd, void* buf, uint8_t len);

  private:
};

#endif
