#ifndef __RACING_H__
#define __RACING_H__

#include "config.h"
#include "types.h"
#include "controller.h"
#include "display.h"
#include "gameBase.h"

// These are defined in sprites.h included by the menu.
extern byte track[];
// The length of the track in rows
extern uint16_t TRACKLEN;
extern byte up[];

class Racing: public Game {
  private:
    // This is the offset into the track array of the track line that is
    // currently at row 0 on the display. The next LEDMATRIX_Y-2 elements in
    // the track array will be filling the display.
    uint8_t trackOffset = 0;
    // This will hold the next time in millis that the track needs to be scrolled.
    uint32_t nextScrollTime;
    // Sets the interval between scrolling the track by the next line. Should
    // be larger than gameDelay and will be reduced for every lap.
    uint16_t scrollDelay;
    // Lap counter
    uint8_t laps = 0;
    // The car position
    point car;
    // We flash the car to make it more visible. This is an indicator for
    // wether it is on or off.
    bool carIsOn = true;
  public:
    Racing(Display *d, Controller *c) : Game(d, c) {};
    void reset();
    void update();
    void updateTrack();
    bool updateCar();
};

#endif // __RACING_H__

