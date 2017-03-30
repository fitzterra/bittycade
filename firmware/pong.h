#ifndef __PONG_H__
#define __PONG_H__

#include "config.h"
#include "types.h"
#include "ball.h"
#include "controller.h"
#include "display.h"
#include "gameBase.h"

class Pong: public Game {
  private:
    uint8_t level;
    uint8_t nofBumpers;
    point paddle;
    uint8_t paddleSize;
    point bumpers[2];
    Ball ball;
    void levelUp();
    void updateBumpers();
  public:
    Pong(Display *d, Controller *c) : Game(d, c) {};
    void reset();
    void update();
};

#endif // __PONG_H__

