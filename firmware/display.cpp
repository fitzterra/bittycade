#include "display.h"

Display::Display() {
	lc.shutdown(0, false);
	lc.setIntensity(0, 0);
	lc.clearDisplay(0);
}

void Display::newGame() {
	lc.clearDisplay(0);

	chaos(1500);
	lc.clearDisplay(0);
}

void Display::drawSprite(byte *sprite) {
	for (int r = 0; r < 8; r++) {
		drawRow(r, sprite[r]);
	}
}

void Display::drawRow(uint8_t y, byte row) {
#if DISPLAYROTATE==0
    lc.setRow(0, y, row);
#elif DISPLAYROTATE==90
    lc.setColumn(0, LEDMATRIX_Y-1-y, row);
#elif DISPLAYROTATE==180
    lc.setRow(0, LEDMATRIX_X-1-y, REVBITS(row));
#else
    lc.setColumn(0, y, REVBITS(row));
#endif
}

void Display::drawCol(uint8_t x, byte col) {
#if DISPLAYROTATE==0
    lc.setColumn(0, x, col);
#elif DISPLAYROTATE==90
    lc.setRow(0, x, REVBITS(col));
#elif DISPLAYROTATE==180
    lc.setColumn(0, LEDMATRIX_Y-1-x, REVBITS(col));
#else
    lc.setRow(0, LEDMATRIX_X-1-x, col);
#endif
}

void Display::clear(uint32_t duration) {
	clear();
	delay(duration);
}

void Display::clear() {
	lc.clearDisplay(0);
}

void Display::drawPixel(uint8_t x, uint8_t y, bool on) {
#if DISPLAYROTATE==0
    lc.setLed(0, y, x, on);
#elif DISPLAYROTATE==90
    lc.setLed(0, x, LEDMATRIX_Y-1-y, on);
#elif DISPLAYROTATE==180
    lc.setLed(0, LEDMATRIX_Y-1-y, LEDMATRIX_X-1-x, on);
#else
    lc.setLed(0, LEDMATRIX_X-1-x, y, on);
#endif


}

void Display::drawPixel(uint8_t x, uint8_t y) {
	drawPixel(x, y, true);
}

void Display::drawObject(uint8_t size, point *position) {
    drawObject(size, position, true);
}

void Display::drawObject(uint8_t size, point *position, bool on) {
	for (uint8_t i = 0; i < size; i++) {
        drawPixel(position->x + i, position->y, on);
	}
}

void Display::flashSprite(byte *sprite, uint8_t frames, uint32_t duration) {
	for (uint8_t i = 0 ; i < frames; i++)
	{
		drawSprite(sprite);

		delay(duration);

		clear(duration);
	}
}

void Display::chaos(uint32_t duration) {
	clear();

	uint32_t start = millis();

	while(uint32_t(millis() - start) < duration) {
		uint8_t x = random(0, LEDMATRIX_X);
		uint8_t y = random(0, LEDMATRIX_Y);

		lc.setLed(0, y, x, true);   

		delay(10);
	}

	for(uint8_t i = 0; i<LEDMATRIX_Y; i++) {
		lc.setRow(0, i, 255);
	}

	delay(1000);
}

void Display::test() {
    int8_t x=0, y=0;
    uint8_t b;
    uint32_t d = 100;
    while(1) {
        while(x<LEDMATRIX_X && y<LEDMATRIX_Y) {
            drawPixel(x++, y++, 1);
            delay(d);
        }
        x--; y--;
        while(y>=0) {
            drawPixel(x, y--, 1);
            delay(d);
        }
        y++;
        while(x>=0 && y<LEDMATRIX_Y) {
            drawPixel(x--, y++, 1);
            delay(d);
        }
        x++; y--;
        while(y>=0) {
            drawPixel(x, y--, 1);
            delay(d);
        }
        delay(d);
        clear();
        x=0; y=0;

        b = B10101010;
        drawRow(y, b);
        delay(d*10);
        b = REVBITS(b);
        drawRow(++y, b);
        delay(d*20);
        b = B11110000;
        drawRow(++y, b);
        delay(d*10);
        b = REVBITS(b);
        drawRow(++y, b);
        delay(d*20);
        b = B11001100;
        drawRow(++y, b);
        delay(d*10);
        b = REVBITS(b);
        drawRow(++y, b);
        delay(d*20);
        b = B11101110;
        drawRow(++y, b);
        delay(d*10);
        b = REVBITS(b);
        drawRow(++y, b);
        delay(d*2*20);
        clear();
        x=0; y=0;

        b = B10101010;
        drawCol(x, b);
        delay(d*10);
        b = REVBITS(b);
        drawCol(++x, b);
        delay(d*20);
        b = B11110000;
        drawCol(++x, b);
        delay(d*10);
        b = REVBITS(b);
        drawCol(++x, b);
        delay(d*20);
        b = B11001100;
        drawCol(++x, b);
        delay(d*10);
        b = REVBITS(b);
        drawCol(++x, b);
        delay(d*20);
        b = B11101110;
        drawCol(++x, b);
        delay(d*10);
        b = REVBITS(b);
        drawCol(++x, b);
        delay(d*2*20);
        clear();
        x=0; y=0;
    }
}
