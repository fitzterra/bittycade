#include "breakout.h"

extern byte lost[];
extern byte up[];

void BreakOut::reset() {
    // Always start slow
    gameDelay = 200;
    // Start with a large paddle
    paddleSize = 2;
    controller->objWidth = paddleSize;
    // Set the controller min and max to the menu sprite size
    controller->xMin = 0;
    controller->xMax = LEDMATRIX_X;
    // Position paddle
    paddle.x = controller->xPos;
    paddle.y = LEDMATRIX_Y - 1;

    // Start at level 1
    level = 1;

	setupLevel(level);

	ball.initialise();  
}

void BreakOut::update() {
    paddle.x = controller->xPos;
    //Serial << "paddle x: " << paddle.x << endl;

	switch(ball.move(&paddle, paddleSize)) {
        case bsOut:
	        display->flashSprite(lost, 4, 500); 
            gameOver = true;
	        clearBricks();
            return;
            break;
        case bsIn:
        case bsBounce:
            break;
	}

	display->clear();
    display->drawObject(1, &(ball.position));
    display->drawObject(paddleSize, &paddle);

	updateBricks(&ball);

	for (int i = 0; i < bricks.size(); i++) {
		point *brick = bricks.get(i);

		display->drawPixel(brick->x, brick->y);
	}

}

void BreakOut::levelUp() {
	level++;

	display->flashSprite(up, 3, 500); 

	// A little bit faster now
	gameDelay -= 30;

	setupLevel(level);

	ball.initialise();


}

void BreakOut::spawnBrick(int y, int x) {
	point *position;
	position = (struct point*)malloc(sizeof(struct point));
	position->x = x;
	position->y = y;

	bricks.add(position);
}

void BreakOut::setupLevel(int lvl) {
	// first level, two rows of bricks
	for (int i = 0; i <= lvl; i++) {
		spawnBrick(i, 0);
		spawnBrick(i, 1);
		spawnBrick(i, 2);
		spawnBrick(i, 3);
		spawnBrick(i, 4);
		spawnBrick(i, 5);
		spawnBrick(i, 6);
		spawnBrick(i, 7);
	}
}

void BreakOut::destroyBrick(int i) {
    point *brick = bricks.remove(i);
    free(brick);
}

void BreakOut::updateBricks(Ball *ball) {
    point *brick;

	for (int i = 0; i < bricks.size(); i++) {
		brick = bricks.get(i);

		if (ball->position.x == brick->x && ball->position.y == brick->y) {
            destroyBrick(i);

			int newX = -1 * ball->direction.x;

			if (ball->direction.x == 0 && ball->direction.y == 1) {
				newX = random(2) == 0 ? -1 : 1;
			}

			ball->direction.x = newX;
			ball->direction.y *= -1;
		}
	}

	if (bricks.size() == 0) {
		levelUp();
	}
}

void BreakOut::clearBricks() {
	for (int i=0; i < bricks.size(); i++) {
        destroyBrick(i);
	}
}
