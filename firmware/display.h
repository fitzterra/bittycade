#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <LedControl.h>
#include "config.h"
#include "types.h"

class Display {
  private:
    LedControl lc = LedControl(DIN, CLK, CS, 1);
  public:
    Display();
    void newGame();
    void drawSprite(byte *sprite);
    void drawRow(uint8_t y, byte row);
    void clear(uint32_t duration);
    void clear();
    void drawPixel(uint8_t x, uint8_t y, bool on);
    void drawPixel(uint8_t x, uint8_t y);
    void drawObject(uint8_t size, point *position);
    void flashSprite(byte *sprite, uint8_t frames, uint32_t duration);
    void chaos(uint32_t duration);
};

#endif //__DISPLAY_H__

