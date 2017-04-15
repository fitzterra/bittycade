#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "config.h"
#include "types.h"
#include "controller.h"
#include "display.h"
#include "gameBase.h"
#include <LinkedList.h>

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define STEER_STRAIGHT 0
#define STEER_LEFT     1
#define STEER_RIGHT    2

class Snake: public Game {
  private:
    // The points in the snake body as a linked list
    LinkedList<point*> body;
    // This will hold the next time in millis that the snake needs to be moved
    uint32_t nextMoveTime;
    // Sets the interval between snake moves. Should be larger than gameDelay
    // and will be reduced for every apple eaten.
    uint16_t moveDelay;
    // Indicates the current direction for steering: straight, left or right
    uint8_t steering;
    // Direction we're moving in
	point travelDir;
    // Position of the apple
	point apple;
    // We flash the apple to make it more visible. This is an indicator for
    // wether it is on or off.
    bool appleIsOn = true;
    // Returns the current direction of travel as a cardinal direction (North,
    // East, West or South)
    uint8_t getTravelDir() { return travelDir.x==0 ? (travelDir.y==1 ? SOUTH : NORTH) : (travelDir.y==1 ? EAST : WEST); };
    // Allocates memory for a new body segment and sets the x,y pos
	point* spawnSegment(int x, int y);
    // Randomly finds a new position for an apple
    void addApple();
    // Updates steering based on any activated buttons
    void checkSteering();
    // Checks if the head has collided with anything
    bool checkCollisions();
    // Moves the snake body to the next position and eats apples
    void moveBody();
    // Destroys the body segments by freeing memory and clearing the list
    void destroyBody();
  public:
    Snake(Display *d, Controller *c) : Game(d, c) {};
    void reset();
    void update();
};

#endif // __SNAKE_H__

