#ifndef __TYPES_H__
#define __TYPES_H__

struct point {
  int8_t x;
  int8_t y;
};

enum games { gmMenu = 0, gmPong = 1, gmTedshow = 2, gmSpaceInvaders = 3, gmSnake = 4, gmBreakOut = 5, gmRacing = 6};

enum tedShowState { tsLights, tsFalling };

enum ballState { bsBounce, bsOut, bsIn };

enum hitKind { hkTop, hkSide, hkNone };

#endif // __TYPES_H__
