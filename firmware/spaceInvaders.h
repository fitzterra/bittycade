#ifndef __SPACEINV_H__
#define __SPACEINV_H__

#include "config.h"
#include "types.h"
#include "controller.h"
#include "display.h"
#include "gameBase.h"
#include <LinkedList.h>

#define INVADERS_PER_LINE  3
#define MOVE_RIGHT 1
#define MOVE_LEFT -1
#define MISSILEDELAY 200

class SpaceInvaders: public Game {
  private:
	int level = 1;
    point ship;
	LinkedList<point*> invaders;
    point *outMissile, *inMissile;
    uint32_t outMissileMove, inMissileMove;
    point *spawnInvader(uint8_t y, uint8_t x, LinkedList<point*> *ll);
    uint8_t invadersDir = MOVE_RIGHT;
    uint32_t nextInvadersMove;
    uint32_t invadersMoveDelay = 750;
    // Will be set to true next time we need to change the invaders dir
    bool changeInvDir = false;
    void moveInvaders();
    void updateShipMissile();
    void destroyInvader(uint8_t i);
    void setupLevel();
  public:
    SpaceInvaders(Display *d, Controller *c) : Game(d, c) {};
    void reset();
    void update();
};

#endif // __SPACEINV_H__
//----------------------------
/*
#pragma once
class SpaceInvaders
{
  private:
    LinkedList<point*> enemies;
    int level = 1;
    point *myBullet;
	point *invaderBullet;
    int myBulletStepDelay = 125;
	int enemyBulletStepDelay = 200;
    long myBulletStep;
	long invaderBulletStep;
    int invaderStepDelay;
    long invaderStep;
    int invaderXDirection;
    int invaderYDirection;
    int invaderBounced;
	void setupLevel(int lvl);
    void spawnInvader(int x, int y);
    void moveInvaders();
    void stepInvader(point *position);
    void detectCollisions();
	void detectShipCollision(point *position);
	void detectEnemyShot(point *position);
	void detectBulletsCollision();
    void gameOver();
    void draw();  
    void drawShip();
    void drawBullets();
    void fire();
	void invaderShoot();
    void resetGame();
  public:
    void update();
    void play();
    void levelUp();
};
*/
