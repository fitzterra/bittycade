#ifndef __BALL_H__
#define __BALL_H__

#include "config.h"
#include "types.h"

class Ball
{
  private:    
    int previousDirection;
    bool between(int val, int min, int max);
    hitKind isHitPaddle(point *paddle, int paddleWidth);    
    int getNewDirection();
  public:
    point position;
    point direction;
	ballState move(point *paddle, int paddleWidth);
    void initialise();
};

#endif // __BALL_H__
