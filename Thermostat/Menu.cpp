#include "Menu.h"

//Main menu objects
MENU_ITEM nullItem;
MENU_ITEM tempItem;
MENU_ITEM modeItem;
MENU_ITEM fanItem;

void Menu_SetupMainMenu()
{
  nullItem = (MENU_ITEM)
  {
    .cursorRow = -1, .cursorCol = -1,
    .printLabel = NULL,
    .printField = NULL,
    .nextItem = { NULL, &tempItem, NULL, &tempItem},
    .btnFn = NULL
  };

  tempItem = (MENU_ITEM)
  {
    .cursorRow = 0, .cursorCol = 0,
    .printLabel = NULL,
    .printField = NULL,
    .nextItem = {&nullItem, NULL, NULL, NULL},
    .btnFn = NULL
  };
}

