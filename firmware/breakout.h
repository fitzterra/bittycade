#ifndef __BREAKOUT_H__
#define __BREAKOUT_H__

#include "config.h"
#include "types.h"
#include "ball.h"
#include "controller.h"
#include "display.h"
#include "gameBase.h"
#include <LinkedList.h>

class BreakOut: public Game {
  private:
	int level = 1;
    point paddle;
    uint8_t paddleSize;
	LinkedList<point*> bricks;
    Ball ball;
	void spawnBrick(int x, int y);
	void setupLevel(int lvl);
	void updateBricks(Ball *ball);
    void destroyBrick(int i);
	void clearBricks();
    void levelUp();
  public:
    BreakOut(Display *d, Controller *c) : Game(d, c) {};
    void reset();
    void update();
};

#endif // __BREAKOUT_H__
