#include "Devices.h"

Switch::Switch(Callback onPress, Callback onRelease, unsigned long debounceDuration) :
	pressHandler(onPress), releaseHandler(onRelease),
	timestamp(0), state(false), debounceDuration(debounceDuration) {}

void Switch::debounce(bool val) {
	unsigned long now = millis();
	if (!state && val) {
		state = true;
		timestamp = now;
		if (pressHandler)
			pressHandler();
	} else if (state && val && (now - timestamp) > debounceDuration) {
		state = false;
		if (releaseHandler)
			releaseHandler();
	}
}

Encoder::Encoder(Callback onLeft, Callback onRight, unsigned long debounceDuration) :
	leftHandler(onLeft), rightHandler(onRight),
	clkTimestamp(0), clkState(false), debounceDuration(debounceDuration) {}

void Encoder::debounce(bool clk, bool dir) {
	unsigned long now = millis();
	if (!clkState && clk) {
		clkState = true;
		clkTimestamp = now;
		if (dir && rightHandler)
			rightHandler();
		if (!dir && leftHandler)
			leftHandler();
	} else if (clkState && !clk && (now - clkTimestamp) > debounceDuration) {
		clkState = false;
	}
}
