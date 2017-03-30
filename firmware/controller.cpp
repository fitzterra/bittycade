#include "controller.h"

Controller::Controller() {
    objWidth = 0;

    pinMode(CONTROLLERRIGHTBUTTONPIN, INPUT_PULLUP);
    pinMode(CONTROLLERLEFTBUTTONPIN, INPUT_PULLUP);
    pinMode(BUTTONLED, OUTPUT);

    update();
}

void Controller::update() {
    // Get the pot analog position
    uint16_t potV = analogRead(CONTROLLERPOTPIN);
    // Set the real X position by mapping the pot value to the correct min and
    // max values after taking objWidth into account.
#ifdef INVERTPOTCONTROLL
    xPos = map(potV, 0, 1023, xMax-objWidth, xMin);
#else
    xPos = map(potV, 0, 1023, xMin, xMax-objWidth);
#endif
    
    // Get the button states.
    // We are using the internal pullups for the buttons, so the state is invereted.
    rightButtonPressed = !digitalRead(CONTROLLERRIGHTBUTTONPIN);
    leftButtonPressed = !digitalRead(CONTROLLERLEFTBUTTONPIN);
  
    // Indicate the state of the right button
    digitalWrite(BUTTONLED, rightButtonPressed);
}

