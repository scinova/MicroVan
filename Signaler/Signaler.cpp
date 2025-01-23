#include <Arduino.h>
#include "Signaler.h"

Signaler::Signaler(unsigned int frontCenterLen_, unsigned int frontSideLen_,
		unsigned int rearCenterLen_, unsigned int rearSideLen_) {

	state.signal = NONE;
	state.visibility = false;
	state.light = OFF;
	state.hazard = false;
	state.brake = false;
	state.reverse = false;
	state.horn = false;

	timestamp.signal = 0;
	timestamp.horn = 0;
	timestamp.light = 0;
	timestamp.brake = 0;

	fstrip.len.center = frontCenterLen_;
	fstrip.len.side = frontSideLen_;
	fstrip.len.total = fstrip.len.center + 2 * fstrip.len.side;
	rstrip.len.center = rearCenterLen_;
	rstrip.len.side = rearSideLen_;
	rstrip.len.total = rstrip.len.center + 2 * rstrip.len.side;
	for (int i = 0; i < fstrip.len.total; i++)
		fstrip.pixels[i] = 0;
	for (int i = 0; i < rstrip.len.total; i++)
		rstrip.pixels[i] = 0;

}

void Signaler::activateLeftTurn() {
	if (state.signal == NONE && !state.hazard && !state.reverse)
		timestamp.signal = millis();
	state.signal = LEFT;
}

void Signaler::activateRightTurn() {
	if (state.signal == NONE && !state.hazard && !state.reverse)
		timestamp.signal = millis();
	state.signal = RIGHT;
}

void Signaler::activateHazard() {
	if (state.signal == NONE && !state.hazard && !state.reverse)
		timestamp.signal = millis();
	state.hazard = true;
}

void Signaler::activateReverse() {
	if (state.signal == NONE && !state.hazard && !state.reverse)
		timestamp.signal = millis();
	state.reverse = true;
}

void Signaler::deactivateTurn() {
	if (!state.hazard && !state.reverse)
		timestamp.signal = millis();
	state.signal = NONE;
}

void Signaler::deactivateHazard() {
	if (state.signal == NONE && !state.reverse)
		timestamp.signal = millis();
	state.hazard = false;
}

void Signaler::deactivateReverse() {
	if (state.signal == NONE && !state.hazard)
		timestamp.signal = millis();
	state.reverse = false;
}

void Signaler::activateVisibility() {
	state.visibility = true;
}

void Signaler::deactivateVisibility() {
	state.visibility = false;
}

void Signaler::activateLowLight() {
	state.light = LOW;
}

void Signaler::activateHighLight() {
	state.light = HIGH;
}

void Signaler::deactivateLight() {
	state.light = OFF;
}

void Signaler::activateBrake() {
	state.brake = true;
	timestamp.brake = millis();
}

void Signaler::deactivateBrake() {
	state.brake = false;
	timestamp.brake = millis();
}

void Signaler::activateHorn() {
	state.horn = true;
	timestamp.horn = millis();
}

void Signaler::deactivateHorn() {
	state.horn = false;
	timestamp.horn = millis();
}

void Signaler::update() {
	// TURN
	unsigned int color = ((millis() - timestamp.signal) % 1000 > 500) ? 0 : 0xFFFFFF;
	if (state.signal == LEFT || state.hazard) {
		for (int i = 0; i < fstrip.len.side; i++)
			fstrip.pixels[i] = color;
		for (int i = 0; i < rstrip.len.side; i++)
			rstrip.pixels[i] = color;
	} else if (state.signal == RIGHT || state.hazard) {
		for (int i = fstrip.len.total - fstrip.len.side; i < fstrip.len.total; i++)
			fstrip.pixels[i] = color;
		for (int i = rstrip.len.total - rstrip.len.side; i < rstrip.len.total; i++)
			rstrip.pixels[i] = color;
	}
}
