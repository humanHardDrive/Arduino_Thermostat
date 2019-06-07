#include "LCDMenu.h"

LCDMenu::LCDMenu(MENU_ITEM* menuList) :
  m_pMenuList(menuList),
  m_bInOption(false),
  m_pLCD(NULL)
{

}

void LCDMenu::addLCD(LiquidCrystal* pLCD, uint8_t nRows, uint8_t nCols)
{
  m_pLCD = pLCD;
  m_nLCDRows = nRows;
  m_nLCDCols = nCols;
}

void LCDMenu::update(uint8_t btn)
{
  if (m_bInOption)
  {
  }
  else
    drawMenuList();
}

void LCDMenu::drawMenuList()
{
  if (m_pLCD && m_pMenuList)
  {
    MENU_ITEM drawItem;
    uint8_t itemIndex = 0;

    memcpy_P(&drawItem, &m_pMenuList[itemIndex], sizeof(MENU_ITEM));

    while (drawItem.cursorRow < m_nLCDRows && drawItem.cursorRow >= 0)
    {
      m_pLCD->setCursor(drawItem.cursorRow, drawItem.cursorCol);

      itemIndex++;
      memcpy_P(&drawItem, &m_pMenuList[itemIndex], sizeof(MENU_ITEM));
    }
  }
}

/*void Menu_DrawMainMenu()
  {
  MENU_ITEM drawItem;
  uint8_t itemIndex = 0;

  memcpy_P(&drawItem, &MAIN_MENU[itemIndex], sizeof(MENU_ITEM));
  while (drawItem.cursorRow < 4 && drawItem.cursorRow >= 0)
  {
    itemIndex++;
    memcpy_P(&drawItem, &MAIN_MENU[itemIndex], sizeof(MENU_ITEM));
  }
  }*/
