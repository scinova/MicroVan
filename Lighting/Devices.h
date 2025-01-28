#ifndef DEVICES_H
#define DEVICES_H

#include <Arduino.h>

typedef void (*Callback)(void);

class Switch {
private:
	Callback pressHandler;
	Callback releaseHandler;
	unsigned long timestamp;
	bool state;
	unsigned long debounceDuration;

public:
	Switch(Callback onPress, Callback onRelease, unsigned long debounceDuration = 10);
	void debounce(bool val);
};

class Encoder {
private:
	Callback rightHandler;
	Callback leftHandler;
	unsigned long clkTimestamp;
	bool clkState;
	bool dtState;
	unsigned long debounceDuration;

public:
	Encoder(Callback onLeft, Callback onRight, unsigned long debounceDuration = 10);
	void debounce(bool clk, bool dt);
};

#endif // DEVICES_H
