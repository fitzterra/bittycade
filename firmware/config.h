#ifndef __CONFIG__H__
#define __CONFIG__H__

#include <stdint.h>
#include <Arduino.h>
// Make Serial streaming available to all
#include <Streaming.h>

// X Size of the LED matrix
#define LEDMATRIX_X 8
// Y Size of the LED matrix
#define LEDMATRIX_Y 8
// Pin potentiometer is connected to
//#define CONTROLLERPOTPIN A0
#define CONTROLLERPOTPIN A7
// To invert the min/max directions of the poteniometer control, define this:
//#define INVERTPOTCONTROLL

// Button pin - will use internal pullup
//#define CONTROLLERRIGHTBUTTONPIN 5
#define CONTROLLERRIGHTBUTTONPIN 2
// Button pin - will use internal pullup
//#define CONTROLLERLEFTBUTTONPIN 4
#define CONTROLLERLEFTBUTTONPIN 3
// Pin to which an LED can be connected which will be lit when the RIGHT button
// is pressed.
#define BUTTONLED 13
// Pins to talk to the LED display
//#define DIN 12
#define DIN 10
//#define CLK 11
#define CLK 12
//#define CS 10
#define CS 11
// This may be changed or defined elsewhere later!
#define NUM_GAMES 6 /// This excludes the Menu which is also handled as a game!
// Size of the menu sprite
#define MENUWIDTH 48
#define MENUHEIGHT 8

#endif // __CONFIG__H__
