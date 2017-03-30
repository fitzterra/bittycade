#include "config.h"
#include "menu.h"
#include "pong.h"

Controller controller;
Display display;
Menu menu(&display, &controller);
Pong pong(&display, &controller);

void setup() 
{
	Serial.begin(115200);
	randomSeed(analogRead(0));
}

void loop() 
{
    uint8_t game = menu.selectGame();
    Serial << "Game: " << game << endl;

    if(game == 0)
        pong.play();
}
