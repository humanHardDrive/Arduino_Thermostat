#ifndef __LCD_MENU_H__
#define __LCD_MENU_H__

#include "Arduino.h"
#include "Menu.h"

#include <LiquidCrystal.h>

class LCDMenu
{
  public:
  LCDMenu(MENU_ITEM* menuList);

  void addLCD(LiquidCrystal pLCD);

  private:
  LiquidCrystal m_pLCD;
  
};

#endif
