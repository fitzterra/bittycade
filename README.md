Bitty Arcade - Extremely Retro, Minimalist, Handheld Arcade Game.
=================================================================

This is my remix of an Arduino based handheld arcade game using an 8x8 LED
matrix as display.

The original inspiration and idea comes from [3CarrotsOnAStick] and is heavily
based on his [AbHhGd] - Arduino Based Hand-held Gaming Device instructable. Most
of the code and game ideas come from here, but I have had to make some heavy
code changes to compile in my environment as well as some changes that I wanted
to the code.

This device also uses the potentiometer as controler, while other devices like
this often uses 4 directional buttons. I decided to stick with the pot for now,
but this may change later.

For now the project is not completed yet, but I have a custom case designed and
it is printing now as I type, and I'm working on the code to allow rotation of
the display in 90° increments. I need this since for my case I had to rotate the
display by 90°, and I also want to clean up the display handling in the original
code which needs the sprites and coordinates to be mirrored.

I'll update here as the project progresses.

Updates
-------

* 2017-05-06: Added option for using a [rotary encoder](#rotEnc) for directional
    control.


<a name="rotEnc"></a>
Rotary Encoder for directional control
--------------------------------------
The initial implementation uses the optimised [Encoder] library by Paul
Stoffregen. The encoder used is a Chinese [knockoff] of the Keyes [KY-040]
rotary encoder.

In order to get this encoder to work, I had to solder a capacitor (100nF) across
each encoder output to ground. This was done right on the encoder on the board.
Without the caps, there would be too much switch bounce with totally erratic
output.

All games current has a delay during the play loop. Due to this delay the
encoder can not be polled for reliable positioning. To get around this for now,
the encoder should be connected to pins that allow external interrupts. For a
Nano or Uno, this will be pins 2 and 3, for example.
The [Encoder] library will automatically use interrupts in this case. It could
be an option to remove the delay in the main games play loop in future in order
to poll the encoder more frequently if using pins that do not support external
interrupts.

When using an encoder, the button on the encoder will also be made available via
the controller, but the individual game has to support this explicitly. An new
`Controller::anyButtonPressed` method has been added which will return true if
any button has been pressed, including an encoder button if available.


[3CarrotsOnAStick]: http://www.instructables.com/member/3CarrotsOnAStick/
[AbHhGd]: http://www.instructables.com/id/AbHhGD-the-Arduino-Based-Hand-held-Gaming-Device/
[Encoder]: http://www.pjrc.com/teensy/td_libs_Encoder.html
[knockoff]:https://www.banggood.com/KY-040-Rotary-Decoder-Encoder-Module-For-Arduino-AVR-PIC-p-914010.html 
[KY-040]: http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/keyes-ky-040-arduino-rotary-encoder-user-manual/ 
