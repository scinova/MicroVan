#ifndef DATETIME_H
#define DATETIME_H

class Date {
public:
	Date(uint16_t year, uint8_t month, uint8_t day)
		: _year(year), _month(month), _day(day) {}

	uint16_t year() const { return _year; }
	uint8_t month() const { return _month; }
	uint8_t day() const { return _day; }

	bool operator==(const Date &date) const {
		return (_year == date._year && _month == date._month && _day == date._day);
	}

	bool operator<(const Date &date) const {
		if (_year != date._year) return _year < date._year;
		if (_month != date._month) return _month < date._month;
		return _day < date._day;
	}

private:
	uint16_t _year;
	uint8_t _month;
	uint8_t _day;
};

class Time {
public:
	Time(uint8_t hour, uint8_t minute, uint8_t second)
		: _hour(hour), _minute(minute), _second(second) {}

	uint8_t hour() const { return _hour; }
	uint8_t minute() const { return _minute; }
	uint8_t second() const { return _second; }

	bool operator==(const Time &time) const {
		return (_hour == time._hour && _minute == time._minute && _second == time._second);
	}

	bool operator<(const Time &time) const {
		if (_hour != time._hour) return _hour < time._hour;
		if (_minute != time._minute) return _minute < time._minute;
		return _second < time._second;
	}

private:
	uint8_t _hour;
	uint8_t _minute;
	uint8_t _second;
};

class DateTime {
public:
	DateTime(const Date &date, const Time &time)
		: _date(date), _time(time) {}

	const Date& date() const { return _date; }
	const Time& time() const { return _time; }

	bool operator==(const DateTime &dt) const {
		return (_date == dt._date && _time == dt._time);
	}

	bool operator<(const DateTime &dt) const {
		if (_date != dt._date) return _date < dt._date;
		return _time < dt._time;
	}

private:
	Date _date;
	Time _time;
};

#endif // DATETIME_H
