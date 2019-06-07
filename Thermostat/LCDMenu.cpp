#include "LCDMenu.h"

void Menu_DrawMainMenu()
{
  MENU_ITEM drawItem;
  uint8_t itemIndex = 0;

  memcpy_P(&drawItem, &MAIN_MENU[itemIndex], sizeof(MENU_ITEM));
  while (drawItem.cursorRow < 4 && drawItem.cursorRow >= 0)
  {
    itemIndex++;
    memcpy_P(&drawItem, &MAIN_MENU[itemIndex], sizeof(MENU_ITEM));
  }
}
