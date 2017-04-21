// This is the game base class

#include "gameBase.h"

void Game::play() {
    // Always start with a reset
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

    // If the last game has allowed pausing, auto clear it here so the next
    // game does not have to worry about clearing it in it's reset method.
    controller->allowPause = false;
}

