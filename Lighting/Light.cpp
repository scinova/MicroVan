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
	loop();
}

void Light::toggleMode() {
	if (mode == WHITE)
		mode = COLOR;
	else
		mode = WHITE;
}

void Light::increaseBrightness() {
	if (state == OFF) {
		brightness = 0;
		state = ON;
	}
	brightness = min(brightness + (1.0 / brightnessSteps), 1.0);
	update();
}

void Light::decreaseBrightness() {
	brightness = std::max(brightness - (1.0 / brightnessSteps), 0.0);
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
	Serial.print(state);
	Serial.print(" ");
	Serial.print(fade);
	Serial.print(" ");
	Serial.print(brightness);
	Serial.print(" ");
	Serial.print(temperature);
	Serial.print(" ");
	Serial.print(rgb.r);
	Serial.print(" ");
	Serial.print(rgb.g);
	Serial.print(" ");
	Serial.print(rgb.b);
	Serial.println(" ");
}

RGB Light::whiteModeRgb() {
	double t = (temperature - WARM_WHITE) / (COOL_WHITE - WARM_WHITE);
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
	double f = (state == FADEIN || state == FADEOUT) ? fade : 1;
	color.r *= brightness * f;
	color.g *= brightness * f;
	color.b *= brightness * f;
	return color;
}

RGB Light::colorModeRgb() {
	// Convert hue from [0.0, 1.0] to [0, 360]
	hue *= 360.0;
	double c = level; // Chroma
	double x = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
	double m = 0; // No offset since we want full brightness
	RGB color;
	// Initialize RGB values based on hue
	if (hue >= 0 && hue < 60) {
		color.r = (c + m) * 255;
		color.g = (x + m) * 255;
		color.b = m * 255;
	} else if (hue >= 60 && hue < 120) {
		color.r = (x + m) * 255;
		color.g = (c + m) * 255;
		color.b = m * 255;
	} else if (hue >= 120 && hue < 180) {
		color.r = m * 255;
		color.g = (c + m) * 255;
		color.b = (x + m) * 255;
	} else if (hue >= 180 && hue < 240) {
		color.r = m * 255;
		color.g = (x + m) * 255;
		color.b = (c + m) * 255;
	} else if (hue >= 240 && hue < 300) {
		color.r = (x + m) * 255;
		color.g = m * 255;
		color.b = (c + m) * 255;
	} else {
		color.r = (c + m) * 255;
		color.g = m * 255;
		color.b = (x + m) * 255;
	}
	// Calculate perceived brightness (luminance)
	double luminance = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
	// Adjust RGB to achieve consistent brightness
	double target_luminance = 128; // Target brightness (can be adjusted)
	double adjustment_factor = target_luminance / (luminance + 1e-6); // Prevent division by zero
	// Adjust RGB values
	color.r = fmin(fmax(color.r * adjustment_factor, 0), 255);
	color.g = fmin(fmax(color.g * adjustment_factor, 0), 255);
	color.b = fmin(fmax(color.b * adjustment_factor, 0), 255);
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
