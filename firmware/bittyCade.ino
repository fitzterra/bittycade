#include "config.h"
#include "menu.h"
#include "pong.h"
#include "breakout.h"
#include "racing.h"

Controller controller;
Display display;
Menu menu(&display, &controller);
Pong pong(&display, &controller);
BreakOut breakout(&display, &controller);
Racing racing(&display, &controller);

void setup() 
{
	Serial.begin(115200);
	randomSeed(analogRead(0));
}

void loop() 
{
    uint8_t game = menu.selectGame();
    Serial << "Game: " << game << endl;

    switch(game) {
        case 0:
            pong.play();
            break;
        case 4:
            breakout.play();
            break;
        case 5:
            racing.play();
            break;
    }
}
