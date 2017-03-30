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
		lc.setColumn(0, r, sprite[r]);
	}
}

void Display::drawRow(uint8_t y, byte row) {
	lc.setColumn(0, y, row);
}

void Display::clear(uint32_t duration) {
	clear();
	delay(duration);
}

void Display::clear() {
	lc.clearDisplay(0);
}

void Display::drawPixel(uint8_t x, uint8_t y, bool on) {
	//lc.setLed(0, y, x, on);
	lc.setLed(0, LEDMATRIX_X-1-x, y, on);
}

void Display::drawPixel(uint8_t x, uint8_t y) {
	drawPixel(x, y, true);
}

void Display::drawObject(uint8_t size, point *position) {
	for (uint8_t i = 0; i < size; i++) {
		//lc.setLed(0, position->y, position->x + i, true);
		lc.setLed(0, LEDMATRIX_X - 1 - (position->x + i), position->y, true);
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
