#include "pong.h"

extern byte lost[];
extern byte up[];
extern int menuStrip[MENUHEIGHT][MENUWIDTH];

void Pong::updateBumpers() {
    point bumper;

	for(int i = 0; i < nofBumpers; i++) {
		bumper = bumpers[i];
	    if (ball.position.x == bumper.x && ball.position.y == bumper.y) {
            int newX = -1 * ball.direction.x;

            if (ball.direction.x == 0 && ball.direction.y == 1)
            {
                newX = random(2) == 0 ? -1 : 1;
            }

            ball.direction.x = newX;
            ball.direction.y *= -1;
        }
	}
}

void Pong::reset() {
    // Always start slow
    gameDelay = 200;
    // Start with a large paddle
    paddleSize = 3;
    controller->objWidth = paddleSize;
    // Set the controller min and max to the menu sprite size
    controller->xMin = 0;
    controller->xMax = LEDMATRIX_X;
    // Position paddle
    paddle.x = (LEDMATRIX_X-1 - paddleSize) / 2;
    paddle.y = LEDMATRIX_Y - 1;

    // Start at level 0
    level = 0;

    // TODO: These should be set up with new, and deleted in a destructor
	// Set up left bumber
	point bumperLeft;
	bumperLeft.x = 2;
	bumperLeft.y = 3;
	bumpers[0] = bumperLeft;
	// Set up right bumber
	point bumperRight;
	bumperRight.x = 5;
	bumperRight.y = 3;
	bumpers[1] = bumperRight;

	// Bumpers will be activated in level 3
	nofBumpers = 0;

    // Prepare the ball
	ball.initialise();  
}

void Pong::update() {
    controller->update();
    paddle.x = controller->xPos;

	updateBumpers();

	switch(ball.move(&paddle, paddleSize)) {
        case bsBounce:
            levelUp();
            break;
        case bsOut:
	        display->flashSprite(lost, 4, 500); 
            gameOver = true;
            return;
            break;
        case bsIn:
            break;
	}

	display->clear();
    display->drawObject(1, &(ball.position));
    display->drawObject(paddleSize, &paddle);

	for(int i = 0; i < nofBumpers; i++) {
		display->drawPixel(bumpers[i].x, bumpers[i].y);
	}
}

void Pong::levelUp() {
	level++;

	if (level % 10 == 0) {
		display->flashSprite(up, 3, 500); 

		// A little bit faster now
		gameDelay -= 30;

		// Time to use smaller paddle
		if (gameDelay < 120) {
            // Reduce paddle size
            paddleSize--;
			controller->objWidth = paddleSize;
            // Reset the delay
			gameDelay = 200;

            // If we are at no paddle, start over
			if (paddleSize == 0)
			{
                // This starts the game from the beginning again, but we do not
                // want to get involved with the menu...
                reset();
                return;
			}
		}

		// At some point, add in the bumpers
		nofBumpers = gameDelay < 150 ? 2 : 0;

		ball.initialise();
	}
}


