#include "spaceInvaders.h"

extern byte lost[];
extern byte up[];

/**
 * Generates a new invader at position x,y by allocating memory for a point
 * structure, and then adding the pointer to this point struct ot the invaders
 * list.
 *
 * @param x: The x coord
 * @param y: The y coord
 * @param ll: pointer to the linked lis to add the point to
 **/
point *SpaceInvaders::spawnInvader(uint8_t y, uint8_t x, LinkedList<point*> *ll) {
	point *position;
	position = (struct point*)malloc(sizeof(struct point));
	position->x = x;
	position->y = y;

	ll->add(position);
    return position;
}

void SpaceInvaders::setupLevel() {
    point *inv;
    // Spawn the invaders - always one row of invaders more than the current
    // level
    for(uint8_t r=0; r<=level; r++) {
        // Now the columns - INVADERS_PER_LINE on a line, with one column open
        // between them
        for(uint8_t c=1, i=0; i<INVADERS_PER_LINE && c<LEDMATRIX_X; i++, c=c+2) {
            inv = spawnInvader(r, c, &invaders);
            display->drawPixel(inv->x, inv->y);
        }
    }
    changeInvDir = false;
    outMissile = NULL;
    inMissile = NULL;
    invadersMoveDelay = 800 - level*100;
}

void SpaceInvaders::moveInvaders() {
    point *inv;
    bool changeDirNext = false;

    for(int8_t i=invaders.size()-1; i>=0; i--) {
        inv = invaders.get(i);
        // Switch it off in old position
        display->drawPixel(inv->x, inv->y, false);
        if(changeInvDir) {
            // We only drop to the next row
            inv->y++;
            // Safety to see if end of screen has been reached. Normally
            // crashing into the ship will be the end, but we do a second check
            // here.
            if(inv->y==LEDMATRIX_Y) {
                gameOver = true;
                return;
            }
        } else {
            // We move in the required dir and check if we need to change the
            // next time we have to move again.
            inv->x += invadersDir;
            if(inv->x<=0 || inv->x>=LEDMATRIX_X-1)
                changeDirNext = true;
        }
        // Hit the ship?
        if(inv->x==ship.x && inv->y==ship.y) {
            gameOver=true;
            return;
        }
        // Draw in new position
        display->drawPixel(inv->x, inv->y);
    }
    // If we dropped down, we are changing direction.
    if(changeInvDir) {
        // Change direction
        invadersDir *= -1;
        // Show that we are done with the change direction
        changeInvDir = false;
        // Decrease delay
        invadersMoveDelay -= 10;
    }
    // Did we detect that a direction change should be done next time?
    if(changeDirNext) {
        // Set it up
        changeInvDir = true;
    }
}

void SpaceInvaders::destroyInvader(uint8_t i) {
    point *inv = invaders.remove(i);
    display->drawPixel(inv->x, inv->y, false);
    free(inv);
}

void SpaceInvaders::reset() {
    display->clear();
    // Always start slow
    gameDelay = 200;
    controller->objWidth = 1;
    // Set the controller min and max to the screen size
    controller->xMin = 0;
    controller->xMax = LEDMATRIX_X;
    controller->update();
    // Position ship
    ship.x = controller->xPos;
    ship.y = LEDMATRIX_Y - 1;
    display->drawPixel(ship.x, ship.y);

    // Start at level 1
    level = 1;

    setupLevel();

    // Slight delay to allow buttons to settle so we do not send a shot off
    // immediatly as the game starts.
    delay(100);
    // Give the user some time to gether bearings before we start moving the
    // invaders.
    nextInvadersMove = millis() + 1000;
}

void SpaceInvaders::updateShipMissile() {
    // Do we have a missile ready to move?
    if(outMissile && millis()>=outMissileMove) {
        // First check if we have hit any invaders
        point *p;
        //Serial << "Mis: " << outMissile->x << "," << outMissile->y << "  Invs:";
        for(int8_t i=invaders.size()-1; i>=0; i--) {
            p = invaders.get(i);
            //Serial << " " << p->x << "," << p->y;
            if(p->x==outMissile->x && p->y==outMissile->y) {
                //Serial << "  bang!";
                destroyInvader(i);
                free(outMissile);
                outMissile=NULL;
                // Any invaders left?
                if(invaders.size()==0) {
                    level++;
                    setupLevel();
                }
                return;
            }
        }

        // No hits, so switch off old position
        display->drawPixel(outMissile->x, outMissile->y, false);
        // Move it in the Y plane
        outMissile->y--;
        // Out of bounds?
        if(outMissile->y<0) {
            free(outMissile);
            outMissile = NULL;
        } else {
            display->drawPixel(outMissile->x, outMissile->y);
        }
        //Serial << endl;
        // Reset the next move time
        outMissileMove = millis() + MISSILEDELAY;
    }
}

void SpaceInvaders::update() {

    // Update the ship
    if(controller->xPos != ship.x) {
        display->drawPixel(ship.x, ship.y, false);
        ship.x = controller->xPos;
        display->drawPixel(ship.x, ship.y);
    }

    // Time to move the invaders?
    if(millis() >= nextInvadersMove) {
        moveInvaders();
        nextInvadersMove = millis() + invadersMoveDelay;
    }

    // Update any ship missile
    updateShipMissile();

    // Fire a missile?
    if(!outMissile && 
       (controller->rightButtonPressed || controller->leftButtonPressed)) {
        outMissile = (struct point*)malloc(sizeof(struct point));
        outMissile->x = ship.x;
        outMissile->y = ship.y-1;
        display->drawPixel(outMissile->x, outMissile->y);
        outMissileMove = millis() + MISSILEDELAY;
    }
    // Clean up on game over
    if(gameOver) {
        while(invaders.size())
            destroyInvader(0);
	    display->flashSprite(lost, 4, 500); 
    }
}

