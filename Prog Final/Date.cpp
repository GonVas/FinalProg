#include "Date.h"
#include <time.h>

Date::Date() // default constructer sets current date , copied from http://www.cplusplus.com/forum/beginner/32329/, credits go to Snarky
{
	day = getTodayDay();
	month = getTodayMonth();
	year = getTodayYear();
	validDay = true;
	validMonth = true;
	validYear = true;
}

Date::Date(unsigned int y, unsigned int m, unsigned int d)
{
	year = y;
	month = m;
	day = d;
	validDay = true;
	validMonth = true;
	validYear = true;
	Validate();
}

Date::Date(string daymonthyear) // constructors can be overloaded
{
	this->year = stoi(extract_from_string(3, daymonthyear, '/', true));
	this->month = stoi(extract_from_string(2, daymonthyear, '/', true));
	this->day = stoi(extract_from_string(1, daymonthyear, '/', true));
	//validDay = true;
	//validMonth = true;
	//validYear = true;
	//Validate();

}

void Date::setstringDate(string date)
{
	year = stoi(extract_from_string(3, date, '/', true));
	month = stoi(extract_from_string(2, date, '/', true));
	day = stoi(extract_from_string(1, date, '/', true));
}

//... DEFINITION OF OTHER MEMBER FUNCTIONS.....

void Date::Validate() //checks to see if date is valid. (It is a simple validation)
{
	if (!(day>0 && day<31))
	{
		validDay = false;
	}
	if (!(month>0 && month<13))
	{
		validMonth = false;
	}
	if (!(year>0))
	{
		validYear = false;
	}
}

bool Date::isLeapYear(int year) // copied from http://www.cplusplus.com/forum/beginner/29832/ credits go to Galik
{
	if (year % 4 != 0)
		return false;
	if (year % 100 != 0)
		return true;
	if (year % 400 == 0)
		return true;
	else
		return false;
}

bool Date::isValid()
{
	return (!(!validDay || !validMonth || !validYear));
}

void Date::setYear(unsigned int y)
{
	year = y;
	Validate();
}

void Date::setMonth(unsigned int m)
{
	month = m;
	Validate();
}

void Date::setDay(unsigned int d)
{
	day = d;
	Validate();
}

void Date::setDate(unsigned int y, unsigned int m, unsigned int d)
{
	year = y;
	month = m;
	day = d;
	Validate();
}

unsigned int Date::getYear() const
{
	return year;
}

unsigned int Date::getMonth() const
{
	return month;
}

unsigned int Date::getDay() const
{
	return day;
}

unsigned int Date::getTodayDay() 
{
	/*time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	return abs(timePtr->tm_mday) ;*/
	return 1;
}

unsigned int Date::getTodayMonth() 
{
	/*time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	return abs(timePtr->tm_mon) ;*/
	return 1;
}

unsigned int Date::getTodayYear()  
{
	/*time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	return (abs(timePtr->tm_year) + 1900) ;*/
	return 1;
}

string Date::getStr()
{
	string date_s;
	date_s += day;
	date_s += '/';
	date_s += month;
	date_s += '/';
	date_s += year;
	return date_s;
}

bool Date::operator==(const Date& rhs) //Allows for two dates two be compared
{
	return (((this->day == rhs.getDay()) && (this->month == rhs.getMonth())) && (this->year == rhs.getYear()));
}

bool Date::operator>(const Date& rhs) //Allows to check with date is older than the other
{
	if ((this->year) > (rhs.year))
	{
		return true;
	}
	else
	{
		if ((this->month) > (rhs.month))
		{
			return true;
		}
		else
		{
			return ((this->day) > (rhs.day));
		}
	}

}

bool Date::operator>=(const Date& rhs)
{
	Date temp(this->year, this->month, this->day);
	bool greater = (temp > rhs);
	if (temp == rhs)
	{
		return true;
	}
	else
	{
		return greater;
	}
}

//Attention DATE class does not have < or <= beacuse they are not needed simply invert the order.

void Date::show() //scope resolution is needed; other classes could have a show() method
{
	cout << day << "/" << month << "/" << year << endl;
}
void Date::save(ofstream & out) const{
	// A IMPLEMENTAR
}

ostream& operator<<(ostream& out, const Date & date)
{
	out << date.day << "/" << date.month << "/" << date.year;
	return out;
}