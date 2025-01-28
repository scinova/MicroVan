#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Devices.h"
#include "Light.h"
#include <stdio.h>
#include <math.h>

#define LEVEL_CLK_PIN 2
#define LEVEL_DIR_PIN 3
#define LEVEL_SWITCH_PIN 4
#define MODE_CLK_PIN 7
#define MODE_DIR_PIN 8
#define MODE_SWITCH_PIN 9

#define PIN 6
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Light light(0.9, 20, 20, 20, 1000);

void handleLevelPress() {
	light.toggle();
}

void handleLevelLeft() {
	light.increaseBrightness();
}

void handleLevelRight() {
	light.decreaseBrightness();
}

void handleModePress() {
	light.toggleMode();
}

void handleModeLeft() {
	if (light.mode == Light::WHITE)
		light.increaseTemperature();
	if (light.mode == Light::COLOR)
		light.increaseHue();
}

void handleModeRight() {
	if (light.mode == Light::WHITE)
		light.decreaseTemperature();
	if (light.mode == Light::COLOR)
		light.decreaseHue();
}

Encoder levelEncoder(&handleLevelLeft, &handleLevelRight);
Switch levelSwitch(&handleLevelPress, NULL);

Encoder modeEncoder(&handleModeLeft, &handleModeRight);
Switch modeSwitch(&handleModePress, NULL);

void driveNeoPixelLed(Adafruit_NeoPixel &pixels, Light &light) {
	for (int i = 0; i < NUMPIXELS; i++) {
		pixels.setPixelColor(i, light.rgb().r * 255, light.rgb().g * 255, light.rgb().b * 255);
	}
	pixels.show();
}

void setup() {
	Serial.begin(115200);
	pixels.begin();
	pinMode(LEVEL_SWITCH_PIN, INPUT_PULLUP);
	pinMode(LEVEL_CLK_PIN, INPUT_PULLUP);
	pinMode(LEVEL_DIR_PIN, INPUT_PULLUP);
	pinMode(MODE_SWITCH_PIN, INPUT_PULLUP);
	pinMode(MODE_CLK_PIN, INPUT_PULLUP);
	pinMode(MODE_DIR_PIN, INPUT_PULLUP);
}

void loop() {
	levelSwitch.debounce(!digitalRead(LEVEL_SWITCH_PIN));
	levelEncoder.debounce(!digitalRead(LEVEL_CLK_PIN), !digitalRead(LEVEL_DIR_PIN));
	modeSwitch.debounce(!digitalRead(MODE_SWITCH_PIN));
	modeEncoder.debounce(!digitalRead(MODE_CLK_PIN), !digitalRead(MODE_DIR_PIN));
	driveNeoPixelLed(pixels, light);
	light.loop();
}
