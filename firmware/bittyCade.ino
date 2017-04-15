#include "config.h"
#include "types.h"
#include "menu.h"
#include "pong.h"
#include "breakout.h"
#include "racing.h"
#include "snake.h"

Controller controller;
Display display;
Menu menu(&display, &controller);
Pong pong(&display, &controller);
BreakOut breakout(&display, &controller);
Racing racing(&display, &controller);
Snake snake(&display, &controller);

void setup() {
	Serial.begin(115200);
	randomSeed(analogRead(0));
}

void loop() {
    games game = menu.selectGame();
    Serial << "Game: " << game << endl;

    switch(game) {
        case gmPong:
            pong.play();
            break;
        case gmTedshow:
        case gmSpaceInvaders:
            break;
        case gmSnake:
            snake.play();
            break;
        case gmBreakOut:
            breakout.play();
            break;
        case gmRacing:
            racing.play();
            break;
    }
}
