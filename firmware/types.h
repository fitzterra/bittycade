#ifndef __TYPES_H__
#define __TYPES_H__

struct point {
  int8_t x;
  int8_t y;
};

enum games { gmPong, gmSpaceInvaders, gmSnake, gmBreakOut, gmRacing};

enum tedShowState { tsLights, tsFalling };

enum ballState { bsBounce, bsOut, bsIn };

enum hitKind { hkTop, hkSide, hkNone };

#endif // __TYPES_H__
