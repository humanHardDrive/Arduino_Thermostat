#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

enum
{
  CENTER_BTN = 0,
  UP_BTN,
  DOWN_BTN,
  LEFT_BTN,
  RIGHT_BTN,
  ALL_BTNS
};

class MenuItem
{
  public:
  MenuItem();
  ~MenuItem();

  virtual void onFocusGained();
  virtual void onFocusLost();

  virtual void handleButtonPress(unsigned char btn);

  virtual void draw();

  protected:
  MenuItem* connectedItems[ALL_BTNS];
  unsigned char focusLevel;

  private:
  void handleSoftFocusBtnPress(unsigned char btn);
  void handleHardFocusBtnPress(unsigned char btn); 
};

#endif
