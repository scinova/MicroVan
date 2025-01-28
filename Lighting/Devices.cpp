#include "Devices.h"

Switch::Switch(Callback onPress, Callback onRelease, unsigned long debounceDuration_) {
	pressHandler = onPress;
	releaseHandler = onRelease;
	timestamp = 0;
	state = false;
	debounceDuration = debounceDuration_;
}

void Switch::debounce(bool val) {
	unsigned long now = millis();
	if (!state && val) {
		state = true;
		if (pressHandler)
			pressHandler();
		timestamp = now;
	} else if (state && !val) {
		if (now - timestamp >= debounceDuration) {
			state = false;
			if (releaseHandler)
				releaseHandler();
			timestamp = now;
		}
	}
}

Encoder::Encoder(Callback onLeft, Callback onRight, unsigned long debounceDuration_) {
	leftHandler = onLeft;
	rightHandler = onRight;
	clkTimestamp = 0;
	clkState = false;
	debounceDuration = debounceDuration_;
}

void Encoder::debounce(bool clk, bool dt) {
	unsigned long now = millis();
	if (clk != clkState) {
		if ((now - clkTimestamp) >= debounceDuration) {
			clkState = clk;
			clkTimestamp = now;
			if (clkState) {
				if (!dt && leftHandler) {
					leftHandler();
				} else if (dt && rightHandler) {
					rightHandler();
				}
			}
		}
	}
}

/*void Encoder::debounce(bool clk, bool dt) {
  unsigned long now = millis();
  if ((now - clkTimestamp) < debounceDuration) return; // Debounce guard

  // State machine for quadrature decoding
  static uint8_t state = 0; // Holds previous and current states
  state = (state << 2) | (clk << 1) | dt;

  switch (state & 0x0F) {
    case 0b0001: case 0b0111: case 0b1110: case 0b1000:
      if (leftHandler) leftHandler();
      clkTimestamp = now;
      break;
    case 0b0010: case 0b1011: case 0b1101: case 0b0100:
      if (rightHandler) rightHandler();
      clkTimestamp = now;
      break;
  }
}*/