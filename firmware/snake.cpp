#include "snake.h"

extern byte lost[];

/**
 * Generates a point at the given coordinates and returns a pointer to it.
 * The point is dynamically allocated and must be freed again when it is not needed anymore.
 **/
point* Snake::spawnSegment(int x, int y) {
	point *position;
	position = (struct point*)malloc(sizeof(struct point));
	position->x = x;
	position->y = y;

	return position;
}

/**
 * Adds and displays an apple at a new random position.
 **/
void Snake::addApple() {
    point *segment;
    bool isClear;

    // Continue looking for a spot to place the apple
    do {
        // Assume it's clear to start with
        isClear = true;
        // Find a random spot
        apple.x = random(LEDMATRIX_X);
        apple.y = random(LEDMATRIX_Y);
        // Is it on the snake?
        for(int8_t i=body.size()-1; i>=0; i--) {
            segment = body.get(i);
            if(segment->x==apple.x && segment->y==apple.y) {
                isClear = false;
                break; // Jump out of for
            }
        }
    } while(!isClear);

    // Display it
    display->drawPixel(apple.x, apple.y);
    appleIsOn = true;
}

/**
 * Checks if a button is pressed and updates the steering position to left or
 * right if so.
 **/
void Snake::checkSteering() {
    if(controller->rightButtonPressed && !controller->leftButtonPressed)
        steering = STEER_RIGHT;
    else if(controller->leftButtonPressed && !controller->rightButtonPressed)
        steering = STEER_LEFT;
    //Serial << "steering: " << steering << endl;
}

/**
 * Checks if the snake has collided with the sides or is eating itself.
 * Returns true if so, false otherwise.
 **/
bool Snake::checkCollisions() {
    // Is the head outside the screen?
    point *head = body.get(0);
    if(head->x < 0 || head->y < 0 ||
       head->x >= LEDMATRIX_X || head->y >= LEDMATRIX_Y) {
        //Serial << "snake in the grass...\n";
        return true;
    }
    
    // Am I eating myself?
    point *seg;
    for(uint8_t i=body.size()-1; i>0; i--) {
        seg = body.get(i);
        if(head->x==seg->x && head->y==seg->y) {
            //Serial << "eat myself at " << i << endl;
            return true;
        }
    }

    return false;
}

/**
 * Moves the body by moving the head in the steering position, and moving all
 * other segments up one. See the SnakeSteering drawing in the docs for info on
 * how the new head position is determined.
 * If the head ends up on the apple, the body is extended by keeping the last
 * tail section. A new apple will also be spawned.
 * No checking for collisions are done.`
 **/
void Snake::moveBody() {
    // If we're not steering straight, we need to change the travel direction
    // point
    if(steering != STEER_STRAIGHT) {
        // See the SnakeSteering diagram in the docs for details on this
        // algorithm.
        // Get the current cardinal direction we're going in, and "turn" into
        // the direction the player wants to steer to so we get the new
        // cardinal direction we should go to.
        int8_t destDir = getTravelDir() + (steering==STEER_RIGHT ? 1 : -1);
        // Check for wrap around
        if(destDir>WEST)
            destDir = NORTH;
        else if(destDir<NORTH)
            destDir = WEST;

        // Temp holder for new x and y travel direction indicators
        int8_t x, y;
        // Update the direction modifier
        if( (steering==STEER_RIGHT && (destDir==EAST || destDir==WEST)) ||
            (steering==STEER_LEFT && (destDir==NORTH || destDir==SOUTH)) ) {
            x = travelDir.y * -1;
            y = travelDir.x * -1;
        } else {
            x = travelDir.y;
            y = travelDir.x;
        }
        // Set new travel direction and steer straight
        travelDir.x = x;
        travelDir.y = y;
        steering = STEER_STRAIGHT;
    }

    // Spawn a new head
    point *head = body.get(0);
    point *newHead = spawnSegment(head->x+travelDir.x, head->y+travelDir.y);
    // Wrap out of the screen?
    if(newHead->x < 0)
        newHead->x = LEDMATRIX_X-1;
    else if(newHead->x >= LEDMATRIX_X)
        newHead->x = 0;
    if(newHead->y < 0)
        newHead->y = LEDMATRIX_Y-1;
    else if(newHead->y >= LEDMATRIX_Y)
        newHead->y = 0;
    // Add it at the head of the body and light the pixel
    body.unshift(newHead);
    display->drawPixel(newHead->x, newHead->y);
    // Has the new head now eaten the apple?
    if(newHead->x==apple.x && newHead->y==apple.y) {
        // Short animation
        for(uint8_t n=0; n<body.size(); n++) {
            head = body.get(n);
            display->drawPixel(head->x, head->y, false);
            delay(40);
            display->drawPixel(head->x, head->y, true);
            delay(50);
        }
        // Give the player some time to choose a button for direction
        nextMoveTime += 500;
        // Spawn a new apple
        addApple();
        // Speed up
        moveDelay -= 50;
    } else {
        // Remove the last tail segment and switch off the pixel
        point *tail = body.pop();
        display->drawPixel(tail->x, tail->y, false);
        free(tail);
    }
}

/**
 * Destroys the whole snake body by freeing the memory for each segment and
 * emptying the linked list.
 **/
void Snake::destroyBody() {
    point *seg;

    while(body.size()) {
        seg = body.pop();
        free(seg);
    }
}

/**
 * Resets the game parameters for starting a new game.
 **/
void Snake::reset() {
    point *segment;

    // Re-seed the random generator
    randomSeed(analogRead(0));

    display->clear();
    moveDelay = 750;
    nextMoveTime = millis() + moveDelay;

    // Set up and draw the first 4 segments of the body
    for(uint8_t x=4; x<8; x++) {
        segment = spawnSegment(x, 4);
        body.add(segment);
        display->drawPixel(segment->x, segment->y);
    }
    // Start moving left
	travelDir.x = -1;
	travelDir.y = 0;
    steering = STEER_STRAIGHT;

    addApple();

    // Give buttons a sec to settle from the press from the menu
    delay(1000);
}

void Snake::update() {
    uint32_t static appleDelay=0, buttonDelay=0;

    // We check for steering changes on every update even if it is not time to
    // move the snake. This allows the player to adjust the steering in advanve
    // before the next body move.
    if(millis() > buttonDelay) {
        checkSteering();
        buttonDelay = millis() + 50;
    }

    // Time to move the snake?
    if(millis() >= nextMoveTime) {
        moveBody();
        if (checkCollisions()) {
            display->flashSprite(lost, 4, 500);
            destroyBody();
            gameOver = true;
            return;
        }
        nextMoveTime = millis() + moveDelay;
    }

    // Flash apple
    if(millis() > appleDelay) {
        appleIsOn = !appleIsOn;
        display->drawPixel(apple.x, apple.y, appleIsOn);
        appleDelay = millis() + 300;
    }
}

