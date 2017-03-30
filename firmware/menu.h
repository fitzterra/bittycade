#ifndef __MENU_H__
#define __MENU_H__

#include <stdint.h>
#include "config.h"
#include "controller.h"
#include "display.h"
#include "gameBase.h"

class Menu: public Game {
private:
    uint8_t selectedGame;
public:
    uint8_t selectGame();
    Menu(Display *d, Controller *c) : Game(d, c) {};
    void reset();
    void update();
};

#endif // __MENU_H__

