#ifndef __MENU_H__
#define __MENU_H__

#include <stdint.h>
#include "config.h"
#include "controller.h"
#include "display.h"
#include "gameBase.h"

class Menu: public Game {
private:
    uint8_t currGame;
public:
    games selectGame();
    Menu(Display *d, Controller *c) : Game(d, c) {currGame=0;};
    void reset();
    void update();
};

#endif // __MENU_H__

