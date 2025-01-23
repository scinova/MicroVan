#include <Arduino.h>
#include "Signaler.h"
#include "SignalerControl.h"
#include "SignalerLeds.h"

// Pin definitions
#define FDATA_SWITCH_PIN 6   // Front LED data pin
#define RDATA_SWITCH_PIN 7   // Rear LED data pin
#define LEFT_TURN_SWITCH_PIN 2
#define RIGHT_TURN_SWITCH_PIN 3
#define HAZARD_SWITCH_PIN 4
#define VISIBILITY_SWITCH_PIN 5
#define LOW_LIGHT_SWITCH_PIN 8
#define HIGH_LIGHT_SWITCH_PIN 9
#define HORN_SWITCH_PIN 10
#define BRAKE_SWITCH_PIN 11
#define REVERSE_SWITCH_PIN 12

Signaler signaler(10, 10, 10, 10); // Initialize with lengths for front and rear strips
SignalerControl control(signaler, LEFT_TURN_SWITCH_PIN, RIGHT_TURN_SWITCH_PIN, HAZARD_SWITCH_PIN, VISIBILITY_SWITCH_PIN, LOW_LIGHT_SWITCH_PIN, HIGH_LIGHT_SWITCH_PIN, HORN_SWITCH_PIN, BRAKE_SWITCH_PIN, REVERSE_SWITCH_PIN);
SignalerLeds leds(signaler, FDATA_SWITCH_PIN, RDATA_SWITCH_PIN);

void setup() {
	Serial.begin(9600);
	// Initialize the LEDs
	leds.update();
  
	// Initialize button inputs
	pinMode(LEFT_TURN_SWITCH_PIN, INPUT_PULLUP);
	pinMode(RIGHT_TURN_SWITCH_PIN, INPUT_PULLUP);
	pinMode(HAZARD_SWITCH_PIN, INPUT_PULLUP);
	pinMode(VISIBILITY_SWITCH_PIN, INPUT_PULLUP);
	pinMode(LOW_LIGHT_SWITCH_PIN, INPUT_PULLUP);
	pinMode(HIGH_LIGHT_SWITCH_PIN, INPUT_PULLUP);
	pinMode(HORN_SWITCH_PIN, INPUT_PULLUP);
	pinMode(BRAKE_SWITCH_PIN, INPUT_PULLUP);
	pinMode(REVERSE_SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
	// Simulate button presses to control the signaler
	if (digitalRead(LEFT_TURN_SWITCH_PIN) == LOW) {
		control.turnLeftOn();
	} else {
		control.turnLeftOff();
	}
  
	if (digitalRead(RIGHT_TURN_SWITCH_PIN) == LOW) {
		control.turnRightOn();
	} else {
		control.turnRightOff();
	}
  
	if (digitalRead(HAZARD_SWITCH_PIN) == LOW) {
		control.hazardOn();
	} else {
		control.hazardOff();
	}

	// Update the signaler state
	signaler.update();

	// Update the LEDs based on the current state
	leds.update();

	// Add a small delay to avoid rapid looping
	delay(100);
}
