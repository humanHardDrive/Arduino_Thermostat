#ifndef __LCD_MENU_H__
#define __LCD_MENU_H__

#include "Arduino.h"
#include "Menu.h"

#include <LiquidCrystal.h>

class LCDMenu
{
  public:
    LCDMenu(MENU_ITEM* menuList);

    void addLCD(LiquidCrystal* pLCD, uint8_t nRows, uint8_t nCols);

    void setItemLabelFn(uint8_t index, void (*printLabelFn)(void));
    void setItemFieldFn(uint8_t index, void (*printFieldFn)(void));
    void setBtnFn(uint8_t index, bool (*btnFn)(uint8_t));

    void update(uint8_t btn);

  private:
    void drawMenuList();

  private:
    LiquidCrystal* m_pLCD;
    uint8_t m_nLCDRows, m_nLCDCols;

    MENU_ITEM* m_pMenuList;

    bool m_bInOption;
};

#endif
