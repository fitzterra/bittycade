#include "controller.h"

Controller::Controller() {
    objWidth = 0;

    pinMode(CONTROLLERRIGHTBUTTONPIN, INPUT_PULLUP);
    pinMode(CONTROLLERLEFTBUTTONPIN, INPUT_PULLUP);
    pinMode(BUTTONLED, OUTPUT);

    update();
}

void Controller::updateButtons() {
    // We are using the internal pullups for the buttons, so the state is invereted.
    rightButtonPressed = !digitalRead(CONTROLLERRIGHTBUTTONPIN);
    leftButtonPressed = !digitalRead(CONTROLLERLEFTBUTTONPIN);
}

void Controller::pause() {
    // We only enter this state when pausing is allowed and both buttons have
    // been pressed. Wait until both buttons have been released
    do {
        delay(100);
        updateButtons();
    } while(rightButtonPressed && leftButtonPressed);

    // Now we pause until any button is pressed to unpause
    do {
        delay(100);
        updateButtons();
    } while(!(rightButtonPressed || leftButtonPressed));

    // Unpaused, but wait for both buttons to be released again
    do {
        delay(100);
        updateButtons();
    } while(rightButtonPressed && leftButtonPressed);
}

void Controller::update() {
    // Get the pot analog position
    uint16_t potV = analogRead(CONTROLLERPOTPIN);
    //Serial << "pot: " << potV << endl;
    // Set the real X position by mapping the pot value to the correct min and
    // max values after taking objWidth into account.
#ifdef INVERTPOTCONTROLL
    xPos = map(potV, 0, 1023, xMax-objWidth, xMin);
#else
    xPos = map(potV, 0, 1023, xMin, xMax-objWidth);
#endif
    
    // Get the button states.
    updateButtons();

    // Pausing?
    if (allowPause && rightButtonPressed && leftButtonPressed)
        pause();
  
    // Indicate the state of the right button
    digitalWrite(BUTTONLED, rightButtonPressed);
}

