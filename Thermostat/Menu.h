#ifndef __MENU_H__
#define __MENU_H__

#include <Arduino.h>
#include <LiquidCrystal.h>

class Menu
{
  public:
  typedef enum
  {
    UP_BTN = 0,
    DWN_BTN,
    LEFT_BTN,
    RIGHT_BTN,
    OK_BTN,
    TOTAL_BTN
  }BUTTON;
  
  public:
  Menu(LiquidCrystal* lcd);

  void handleButtonPress(BUTTON btn);

  private:
  LiquidCrystal* m_pLCD;
};

#endif
