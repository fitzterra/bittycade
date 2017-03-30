// This is the game base class

#include "gameBase.h"

void Game::play() {
    reset();

    // This should be done in reset, but let's make sure here
    gameOver = false;

    while(!gameOver) {
        // Read and update the controlls
        controller->update();
        // Update my state and the display
        update();
        // Keep things playable
        delay(gameDelay);
    }
}

