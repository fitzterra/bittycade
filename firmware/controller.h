#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <stdint.h>
#include "config.h"
#include "types.h"
#if DIRCONTR==CONTRL_ROTARY
    #include <Encoder.h>
#endif

class Controller {
private:
    void pause();
    void updateButtons();
#if DIRCONTR==CONTRL_POT
    void updatePot();
#else
    Encoder encoder = Encoder(ROTARY_A, ROTARY_B);
    void updateEncoder();
#endif
public:
    // The minimum value to map the analog pot input or rotary encoder position
    // to. This will normally be 0, but the game can set this to any value for
    // special needs. It will be used as the minimum to map the pot value or 0
    // - 1023 to.
    int16_t xMin;
    // The maximum value to map the analog pot input or rotary encoder position
    // to. This will normally be LEDMATRIX_X-1, but the game can set this to
    // any value for special needs.  It will be used as the minimum, after
    // subtracting objWidth, to map the pot value or 0 - 1023 to. Also see
    // objWidth below.
    int16_t xMax;
    // Allows the width of the object being controlled by the
    // poteniometer/encoder to be specified. If this is done, the X position
    // will always be between 0 and (xMax-objWidth) which makes it easy to know
    // the X pos of where to draw the controlled object. 
    uint8_t objWidth;
    // This will be X position based on the position of the pot or rotary
    // encoder, the min and max values for the mapping of the raw analog value,
    // or limiting the rotary counter, and the objWidth value above. See
    // update() for more info.
    int16_t xPos;
    // Button states.
    bool rightButtonPressed;
    bool leftButtonPressed;
#if DIRCONTR==CONTRL_ROTARY
    bool rotaryButtonPressed;
#endif
    // If the game allows pausing
    bool allowPause = false;

    // Constructor
    Controller();

    /**
     * Controller state update method.
     * Reads the controls and updates xPos and the button states.
     * The analog value read from the pot is mapped to a min and max value
     * controlled by xMin, xMax and objWidth. See the respective documentation
     * for each member.
     * This automatic mapping allows the X position of where the controlled
     * object needs to be positioned, to be determined exactly without any
     * further computation in any instance using the controller.
     ***/
    void update();

    /**
     * Returns true if any defined button is pressed. False otherwise.
     **/
    bool anyButtonPressed();

    /**
     * Forces the controller X Position to a specific position.
     *
     * @param xp: the new position in the range xMin to xMax
     **/
    void setXpos(uint16_t xp) {encoder.write(xp*4);};
};

#endif // __CONTROLLER_H__
