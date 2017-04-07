/**
 * Classic down scrolling track with the player controlling a car that has to
 * avoid the obsticles.
 */
#include "racing.h"

/**
 * Method to scroll the track at a specific rate based on the current lap.
 **/
void Racing::updateTrack() {
    // Get out of here if we do not need to scroll the track
    if (millis() < nextScrollTime) 
        return;

    // We need to scroll.
    // Update the offset and set the row we will be drawing at the top of the
    // display.
    int16_t row = ++trackOffset;

    // Update the screen
    for(uint8_t r=0; r<LEDMATRIX_Y; r++, row--) {
        // We draw the row from the track, unless we are outside the track
        // since this may be the start of the track sliding down, in which case
        // we blank the row.
        display->drawRow(r, row>=0 ? track[row] : B00000000);
    }

    nextScrollTime = millis() + scrollDelay;
}

/**
 * Updates and displays the car position, and tests for crashes.
 *
 * Returns true if the car crashed, false otherwise
 **/
bool Racing::updateCar() {
    // Update the postion
    car.x = controller->xPos;

    // Calculate the row offset into the track the car is at
    int16_t carTrackOffs = trackOffset - car.y;
    // Get the track row
    byte trackRow = carTrackOffs>=0 ? track[carTrackOffs] : 0;

    bool crash = trackRow & (1<<car.x);

    // If the car is on, merge it onto the track
    if(carIsOn)
        trackRow |= (1 << car.x);

    // Update display
    display->drawRow(car.y, trackRow);

    // Toggle car visibility
    carIsOn = !carIsOn;

    return crash;
}

void Racing::update() {
    //car = controller->xPos;

    // First we update the track
    updateTrack();

    // Update car and check for crash
    if(updateCar()) {
        display->chaos(3000);
        gameOver = true;
        return;
    }

    // End of lap?
    if(trackOffset==TRACKLEN-1) {
        laps++;
        scrollDelay -= 100;
        trackOffset = 0;
	    display->flashSprite(up, 4, 500); 
    }
}

// This is called right before the game starts
void Racing::reset() {
    // The car is one pixel wide, set that as the object with we are
    // controlling.
    controller->objWidth = 1;
    // Set the controller min and max to the screen size
    controller->xMin = LEDMATRIX_X-1;
    controller->xMax = 0;
    // The overall delay in the game loop
    gameDelay = 50;
    gameOver = false;
    // Start at the beginning of the track
    trackOffset = 0;

    // The initial scroll delay
    scrollDelay = 600;
    // Force a track update on first run
    nextScrollTime = 0;

    // Car setup
    car.y = LEDMATRIX_Y-2;  // The cars y pos on the screen
    car.x = controller->xPos;
    carIsOn = true;
}
