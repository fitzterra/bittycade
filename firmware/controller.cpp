#include "controller.h"

/**
 * Controller constructor.
 * */
Controller::Controller() {
    objWidth = 0;

    pinMode(CONTROLLERRIGHTBUTTONPIN, INPUT_PULLUP);
    pinMode(CONTROLLERLEFTBUTTONPIN, INPUT_PULLUP);
    pinMode(BUTTONLED, OUTPUT);
#if DIRCONTR==CONTRL_ROTARY
    pinMode(ROTARY_BUTTON, INPUT_PULLUP);
#endif

    update();
}

void Controller::updateButtons() {
    // We are using the internal pullups for the buttons, so the state is invereted.
    rightButtonPressed = !digitalRead(CONTROLLERRIGHTBUTTONPIN);
    leftButtonPressed = !digitalRead(CONTROLLERLEFTBUTTONPIN);
    rotaryButtonPressed = !digitalRead(ROTARY_BUTTON);
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

#if DIRCONTR==CONTRL_POT
void Controller::updatePot() {
    // Get the pot analog position
    uint16_t potV = analogRead(CONTROLLERPOTPIN);
    // Set the real X position by mapping the pot value to the correct min and
    // max values after taking objWidth into account.
#ifdef INVERTPOTCONTROL
    xPos = map(potV, 0, 1023, xMax-objWidth, xMin);
#else
    xPos = map(potV, 0, 1023, xMin, xMax-objWidth);
#endif
}
#else
void Controller::updateEncoder() {
    xPos = encoder.read() / 4;

    if (xPos > xMax-objWidth) {
        xPos = xMax-objWidth;
        encoder.write(xPos * 4);
    } else if (xPos < xMin) {
        xPos = xMin;
        encoder.write(xPos * 4);
    }
}
#endif

void Controller::update() {
#if DIRCONTR==CONTRL_POT
    updatePot();
#else
    updateEncoder();
#endif
    
    // Get the button states.
    updateButtons();

    // Pausing?
    if (allowPause && rightButtonPressed && leftButtonPressed)
        pause();
  
    // Indicate the state of the right button
    digitalWrite(BUTTONLED, rightButtonPressed);
}

bool Controller::anyButtonPressed() {
    bool anyB = leftButtonPressed || rightButtonPressed;

#if DIRCONTR==CONTRL_ROTARY
    anyB = anyB || rotaryButtonPressed;
#endif

    return anyB;
}
