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
// Set the rotation angle if needed - 0, 90, 180 or 270
#define DISPLAYROTATE 90

// Direction control. This can be a potentionmeter or a rotary encoder
#define CONTRL_POT 0
#define CONTRL_ROTARY 1
// Define which control to use here, and define the specific controller
// connections below
//#define DIRCONTR CONTRL_POT
#define DIRCONTR CONTRL_ROTARY


// Pin potentiometer is connected to
#if DIRCONTR==CONTRL_POT
    #define CONTROLLERPOTPIN A7
    // To invert the min/max directions of the poteniometer control, define
    // this:
    //#define INVERTPOTCONTROL
#else
    // Rotary encoder settings
    #define ROTARY_A 3
    #define ROTARY_B 2
    // Will use internal pullup for the button
    #define ROTARY_BUTTON 4
#endif

// Button pin - will use internal pullup
#define CONTROLLERRIGHTBUTTONPIN 5
//#define CONTROLLERRIGHTBUTTONPIN 2
// Button pin - will use internal pullup
#define CONTROLLERLEFTBUTTONPIN 6
//#define CONTROLLERLEFTBUTTONPIN 3
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
#define NUM_GAMES 5 /// This excludes the Menu which is also handled as a game!
// Size of the menu sprite
#define MENUWIDTH NUM_GAMES*8
#define MENUHEIGHT 8

#endif // __CONFIG__H__
