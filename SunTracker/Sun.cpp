#include "Sun.h"

Sun::Sun(double latitude, double longitude)
	: latitude(latitude), longitude(longitude) {}

Sun::SunPosition Sun::getPosition(const DateTime &datetime) {
	double longitudeRadians = RAD * -longitude;
	double latitudeRadians = RAD * latitude;
	double daysSinceEpoch = toDays(datetime);
	SunCoords sunCoords = calculateSunCoords(daysSinceEpoch);
	double hourAngle = calculateSiderealTime(daysSinceEpoch, longitudeRadians) - sunCoords.rightAscension;

	SunPosition position;
	position.azimuth = calculateAzimuth(hourAngle, latitudeRadians, sunCoords.declination);
	position.altitude = calculateAltitude(hourAngle, latitudeRadians, sunCoords.declination);
	return position;
}

double Sun::toJulian(const DateTime &datetime) {
	int year = datetime.date().year();
	int month = datetime.date().month();
	int day = datetime.date().day();
	
	if (month <= 2) {
		year--;
		month += 12;
	}
	int A = year / 100;
	int B = 2 - A + A / 4;
	return static_cast<double>(static_cast<int>(365.25 * (year + 4716))) + 
		static_cast<double>(static_cast<int>(30.6001 * (month + 1))) + 
		day + B - 1524.5;
}

double Sun::toDays(const DateTime &datetime) {
	return toJulian(datetime) - 2451545;
}

double Sun::calculateRightAscension(double longitude, double latitude) {
	return atan2(sin(longitude) * cos(RAD * 23.4397) - tan(latitude) * sin(RAD * 23.4397), cos(longitude));
}

double Sun::calculateDeclination(double longitude, double latitude) {
	return asin(sin(latitude) * cos(RAD * 23.4397) + cos(latitude) * sin(RAD * 23.4397) * sin(longitude));
}

double Sun::calculateAzimuth(double hourAngle, double latitude, double declination) {
	return atan2(sin(hourAngle), cos(hourAngle) * sin(latitude) - tan(declination) * cos(latitude));
}

double Sun::calculateAltitude(double hourAngle, double latitude, double declination) {
	return asin(sin(latitude) * sin(declination) + cos(latitude) * cos(declination) * cos(hourAngle));
}

double Sun::calculateSiderealTime(double daysSinceEpoch, double longitude) {
	return RAD * (280.16 + 360.9856235 * daysSinceEpoch) - longitude;
}

double Sun::calculateSolarMeanAnomaly(double daysSinceEpoch) {
	return RAD * (357.5291 + 0.98560028 * daysSinceEpoch);
}

double Sun::calculateEclipticLongitude(double meanAnomaly) {
	double equationOfCenter = RAD * (1.9148 * sin(meanAnomaly) + 0.02 * sin(2 * meanAnomaly) + 0.0003 * sin(3 * meanAnomaly));
	double perihelion = RAD * 102.9372;
	return meanAnomaly + equationOfCenter + perihelion + PI;
}

Sun::SunCoords Sun::calculateSunCoords(double daysSinceEpoch) {
	double meanAnomaly = calculateSolarMeanAnomaly(daysSinceEpoch);
	double eclipticLongitude = calculateEclipticLongitude(meanAnomaly);
	SunCoords coords;
	coords.declination = calculateDeclination(eclipticLongitude, 0);
	coords.rightAscension = calculateRightAscension(eclipticLongitude, 0);
	return coords;
}
