#include "menu.h"
#include "sprites.h"

void Menu::reset() {
    // Set the controller min and max to the menu sprite size
    controller->xMin = 0;
    controller->xMax = NUM_GAMES;
    // Set the controller object width to the width of one menu
    controller->objWidth = 1;
    // Set the controller to the previous game
    controller->setXpos(currGame);
}

void Menu::update() {
    // Due to how we have set up the controller min, max and objWidth values in
    // the reset() method, the controller xPos will now indicate the column
    // offset into the menu sprite from where we need to start filling the
    // display.
    uint8_t offset = controller->xPos;
    //Serial << "menu offs: " << offset << endl;

    // Display the menu sprite for this game
    display->drawSprite(spriteMenus[offset]);

    // Any button pressed?
    if (controller->anyButtonPressed())
    {
        // Save the currently selected game
        currGame = offset;
        // Indicate game over
        gameOver = true;
    }
}

/**
 * Game selector.
 **/
games Menu::selectGame() {

    // Call the play loop until it exits
    play();

    return games(currGame);
}
