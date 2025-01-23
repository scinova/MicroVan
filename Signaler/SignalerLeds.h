#ifndef SIGNALERLEDS_H
#define SIGNALERLEDS_H

#include <Adafruit_NeoPixel.h>

class SignalerLeds {
private:
	Signaler& signaler;
	Adafruit_NeoPixel fpixels, rpixels;
public:
	SignalerLeds(Signaler& signaler_, int fdataPin, int rdataPin) {
		fpixels = Adafruit_NeoPixel(signaler.fstrip.len.total, fdataPin, NEO_GRB + NEO_KHZ800);
		rpixels = Adafruit_NeoPixel(signaler.rstrip.len.total, rdataPin, NEO_GRB + NEO_KHZ800);
	}

	void update() {
		for (int i = 0; i < signaler.fstrip.len.total; i++)
			fpixels.setColor(i, signaler.fstrip.pixels[i]);
		for (int i = 0; i < signaler.rstrip.len.total; i++)
			rpixels.setColor(i, signaler.rstrip.pixels[i]);
	}
};

#endif // SIGNALERLEDS_H
