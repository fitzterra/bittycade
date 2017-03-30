#include "menu.h"
#include "sprites.h"

void Menu::reset() {
    // Preset selected game
    selectedGame = 0;
    // Set the controller min and max to the menu sprite size
    controller->xMin = 0;
    controller->xMax = MENUWIDTH+1;
    // Set the controller object width to the width of one menu
    controller->objWidth = MENUWIDTH / NUM_GAMES;
}

void Menu::update() {
    // Due to how we have set up the controller min, max and objWidth values in
    // the reset() method, the controller xPos will now indicate the column
    // offset into the menu sprite from where we need to start filling the
    // display.
    uint8_t offset = controller->xPos;

	// Display sprite from offset
	for (int y=0; y<MENUHEIGHT; y++)
	{
		for (int x=0; x<controller->objWidth; x++)
		{
			display->drawPixel(x, y, menuStrip[y][x + offset] == 1);
			//display.drawPixel(y, 7-x, menuStrip[y][x + offset] == 1);
		}
	}

	// Any button pressed?
	if (controller->rightButtonPressed || controller->leftButtonPressed)
	{
        // Calculate the selected game
        selectedGame = offset / (MENUWIDTH / NUM_GAMES);
        // Indicate game over
        gameOver = true;

        // Serial << "offset: " << offset << endl;
	}
}

/**
 * Game selector.
 **/
uint8_t Menu::selectGame() {

    // Call the play loop until it exits
    play();

    return selectedGame;
}
