// Game base class header
#ifndef __GAMEBASE_H__
#define __GAMEBASE_H__

#include <stdint.h>
#include "display.h"
#include "controller.h"

class Game {
    protected:
        // Adjustable time to delay in the play loop
        uint32_t gameDelay;
        // Set to true when game is over
        bool gameOver;
        // Pointer to Display object
        Display *display;
        // Pointer to Controller object
        Controller *controller;
    public:
        /**
         * Constructor
         *
         * @param *d : Pointer to the Display object
         * @param *c : Pointer to the Controller object
         **/
        Game(Display *d, Controller *c) : display(d), controller(c) {};

        /**
         * Reset method.
         *
         * Should reset the game to start values.
         * Called from the play method.
         * Should be overridden by inherited classes.
         **/
       virtual void reset() =0;

       /**
        * The game update method.
        * Called from play() on every play loop to update the game variables
        * and the display. The controller values would already be up to date
        * when this method is called.
        **/
       virtual void update() =0;

       /**
        * Play loop.
        * Called when the game should be played.
        **/
       virtual void play();

};
 	
#	endif // __GAMEBASE_H__
 	
 	
 	
