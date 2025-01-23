#ifndef HEBREWDATETIME_H
#define HEBREWDATETIME_H

#include <cstdint>

class HebrewTime {
public:
	HebrewTime(uint8_t hour, uint32_t parts)
		: _hour(hour), _parts(parts) {}

	uint8_t hour() const { return _hour; }
	uint32_t parts() const { return _parts; }

	bool operator==(const HebrewTime &time) const {
		return (_hour == time._hour && _parts == time._parts);
	}

	bool operator<(const HebrewTime &time) const {
		if (_hour != time._hour) return _hour < time._hour;
		return _parts < time._parts;
	}

private:
	uint8_t _hour;
	uint32_t _parts;
};

class HebrewDate {
public:
	HebrewDate(uint16_t year, uint8_t month, uint8_t day)
		: _year(year), _month(month), _day(day) {}

	uint16_t year() const { return _year; }
	uint8_t month() const { return _month; }
	uint8_t day() const { return _day; }

	bool operator==(const HebrewDate &date) const {
		return (_year == date._year && _month == date._month && _day == date._day);
	}

	bool operator<(const HebrewDate &date) const {
		if (_year != date._year) return _year < date._year;
		if (_month != date._month) return _month < date._month;
		return _day < date._day;
	}

private:
	uint16_t _year;
	uint8_t _month;
	uint8_t _day;
};

#endif // HEBREWDATETIME_H
