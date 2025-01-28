#include "Light.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WARM_WHITE 3500
#define NEUTRAL_WHITE 5000
#define COOL_WHITE 7000

Light::Light(double defaultBrightness_,
		unsigned int brightnessSteps_,
		unsigned int temperatureSteps_,
		unsigned int hueSteps_,
		unsigned long fadeDuration_) {
	defaultBrightness = defaultBrightness_;
	brightnessSteps = brightnessSteps_;
	temperatureSteps = temperatureSteps_;
	hueSteps = hueSteps_;
	fadeDuration = fadeDuration_;
	brightness = defaultBrightness;
	temperature = NEUTRAL_WHITE;
	fade = 0;
	fadeStart = 0;
	fadeTimestamp = 0;
	state = OFF;
	mode = WHITE;
}

void Light::toggle() {
	if (state == OFF) {
		if (brightness < defaultBrightness)
			brightness = defaultBrightness;
		fade = 0;
		state = FADEIN;
	} else if (state == ON) {
		fade = 1;
		state = FADEOUT;
	} else if (state == FADEOUT) {
		state = FADEIN;
	} else if (state == FADEIN) {
		state = FADEOUT;
	}
	fadeTimestamp = millis();
	fadeStart = fade;
}

void Light::toggleMode() {
	if (mode == WHITE)
		mode = COLOR;
	else
		mode = WHITE;
}

void Light::increaseBrightness() {
	if (state == OFF)
		state = ON;
	brightness = min(brightness + (1.0 / brightnessSteps), 1.0);
	update();
}

void Light::decreaseBrightness() {
	brightness = max(brightness - (1.0 / brightnessSteps), 0.0);
	if (brightness == 0)
		state = OFF;
	update();
}

void Light::increaseTemperature() {
	unsigned int step = (COOL_WHITE - WARM_WHITE) / temperatureSteps;
	temperature = min(temperature + step, COOL_WHITE);
	update();
}

void Light::decreaseTemperature() {
	unsigned int step = (COOL_WHITE - WARM_WHITE) / temperatureSteps;
	temperature = max(temperature - step, WARM_WHITE);
	update();
}

void Light::increaseHue() {
	double h = hue + 1.0 / hueSteps;
	hue = (h >= 1 ? h - 1 : h);
	update();
}

void Light::decreaseHue() {
	double h = hue - 1.0 / hueSteps;
	hue = (h < 0 ? h + 1 : h);
	update();
}

void Light::logg() {
	Serial.print(" state: ");
	Serial.print(state);
	Serial.print(" fade: ");
	Serial.print(fade);
	Serial.print(" bright: ");
	Serial.print(brightness);
	Serial.print(" temp: ");
	Serial.print(temperature);
	Serial.print(" rgb: ");
	Serial.print(rgb().r);
	Serial.print(" ");
	Serial.print(rgb().g);
	Serial.print(" ");
	Serial.print(rgb().b);
	Serial.println(" ");
}

RGB Light::whiteModeRgb() {
	RGB color;
	if (temperature <= NEUTRAL_WHITE) {
		color.r = 1.0; 
		color.g = 0.5 + (0.5 * (temperature - WARM_WHITE) / (NEUTRAL_WHITE - WARM_WHITE));
		color.b = 0.25 + (0.25 * (temperature - WARM_WHITE) / (NEUTRAL_WHITE - WARM_WHITE));
	} else {
		color.r = 1.0 - (0.5 * ((temperature - NEUTRAL_WHITE) / (COOL_WHITE - NEUTRAL_WHITE)));
		color.g = 1.0;
		color.b = 0.5 + (0.5 * ((temperature - NEUTRAL_WHITE) / (COOL_WHITE - NEUTRAL_WHITE)));
	}
	double min_value = fmin(fmin(color.r, color.g), color.b);
	double thr = 0.9;
	if (min_value < thr) {
		color.r = color.r < thr ? thr : color.r;
		color.g = color.g < thr ? thr : color.g;
		color.b = color.b < thr ? thr : color.b;
	}
	color.r *= brightness * fade;
	color.g *= brightness * fade;
	color.b *= brightness * fade;
	return color;
}

RGB Light::colorModeRgb() {
	double h = hue * 360.0;
	double s = 1.0;
	double v = brightness * fade;

	double c = v * s;
	double x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
	double m = v - c;

	RGB color;
	if (h >= 0 && h < 60) {
		color.r = c; color.g = x; color.b = 0;
	} else if (h < 120) {
		color.r = x; color.g = c; color.b = 0;
	} else if (h < 180) {
		color.r = 0; color.g = c; color.b = x;
	} else if (h < 240) {
		color.r = 0; color.g = x; color.b = c;
	} else if (h < 300) {
		color.r = x; color.g = 0; color.b = c;
	} else {
		color.r = c; color.g = 0; color.b = x;
	}
	color.r += m;
	color.g += m;
	color.b += m;
	color.r = fmax(fmin(color.r, 1.0), 0.0);
	color.g = fmax(fmin(color.g, 1.0), 0.0);
	color.b = fmax(fmin(color.b, 1.0), 0.0);
	return color;
}

RGB Light::rgb() {
	if (mode == COLOR)
		return colorModeRgb();
	else
		return whiteModeRgb();
}

void Light::update() {
	logg();
}

void Light::loop() {
	unsigned long now = millis();
	if (state == FADEIN || state == FADEOUT) {
		double p = (double)(now - fadeTimestamp) / fadeDuration;
		if (p >= 1) {
			if (state == FADEIN) {
				fade = 1;
				state = ON;
			}
			if (state == FADEOUT) {
				fade = 0;
				state = OFF;
			}
		} else {
			if (state == FADEIN)
				fade = (1 - fadeStart) * p;
			if (state == FADEOUT)
				fade = 1 - (fadeStart * p);
		}
		update();
	}
}
