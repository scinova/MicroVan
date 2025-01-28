#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

typedef struct {
	double r;
	double g;
	double b;
} RGB;

class Light {
private:
	void logg();
	void update();
	RGB whiteModeRgb();
	RGB colorModeRgb();
	double defaultBrightness;
	unsigned int brightnessSteps;
	unsigned int temperatureSteps;
	unsigned int hueSteps;
	unsigned long fadeDuration;
	double fade;
	unsigned long fadeTimestamp;
	double fadeStart;

public:
	enum State {
		OFF,
		FADEIN,
		ON,
		FADEOUT
	};
	enum Mode {
		WHITE,
		COLOR
	};
	double brightness;
	double hue;
	unsigned int temperature;
	State state;
	Mode mode;
	Light(double defaultBrightness = 0.9, 
			unsigned int brightnessSteps = 20, 
			unsigned int temperatureSteps = 20, 
			unsigned int hueSteps = 20,
			unsigned long fadeDuration = 1000);
	void toggle();
	void toggleMode();
	void increaseHue();
	void decreaseHue();
	void increaseBrightness();
	void decreaseBrightness();
	void increaseTemperature();
	void decreaseTemperature();
	void loop();
	RGB rgb();
};

#endif // LIGHT_H
