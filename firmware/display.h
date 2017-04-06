#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <LedControl.h>
#include "config.h"
#include "types.h"

// Macro to reverse (mirror) the bits in an 8 bit byte. Many thanks to
// Sean Eron Anderson <seander@cs.stanford.edu> for publishing it here:
// http://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith32Bits
#define REVBITS(b) (((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16)

class Display {
  private:
    LedControl lc = LedControl(DIN, CLK, CS, 1);
  public:
    Display();
    void newGame();
    void drawSprite(byte *sprite);
    void drawRow(uint8_t y, byte row);
    void drawCol(uint8_t x, byte col);
    void clear(uint32_t duration);
    void clear();
    void drawPixel(uint8_t x, uint8_t y, bool on);
    void drawPixel(uint8_t x, uint8_t y);
    void drawObject(uint8_t size, point *position);
    void flashSprite(byte *sprite, uint8_t frames, uint32_t duration);
    void chaos(uint32_t duration);
    void test();
};

#endif //__DISPLAY_H__

