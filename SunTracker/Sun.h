#ifndef SUN_H
#define SUN_H

#include <cmath>
#include "DateTime.h"

#define PI 3.14159265358979323846
#define RAD (PI / 180)

class Sun {
public:
	struct SunCoords {
		double declination;
		double rightAscension;
	};

	struct SunPosition {
		double azimuth;
		double altitude;
	};

	Sun(double latitude, double longitude);
	SunPosition getPosition(const DateTime &datetime);

private:
	double latitude;
	double longitude;
	double toJulian(const DateTime &datetime);
	double toDays(const DateTime &datetime);
	double calculateRightAscension(double longitude, double latitude);
	double calculateDeclination(double longitude, double latitude);
	double calculateAzimuth(double hourAngle, double latitude, double declination);
	double calculateAltitude(double hourAngle, double latitude, double declination);
	double calculateSiderealTime(double daysSinceEpoch, double longitude);
	double calculateSolarMeanAnomaly(double daysSinceEpoch);
	double calculateEclipticLongitude(double meanAnomaly);
	SunCoords calculateSunCoords(double daysSinceEpoch);
};

#endif // SUN_H
