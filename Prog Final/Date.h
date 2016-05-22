# pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Date.h"
#include "utils.h"

using namespace std;

class Date
{
public: // access specifier; users can only access the PUBLIC members
	Date(); // constructor; constructors have the name of the class
	Date(unsigned int y, unsigned int m, unsigned int d);
	Date(string daymonthyear); // constructors can be overloaded

	void setYear(unsigned int y); // member function OR method
	void setMonth(unsigned int m);
	void setDay(unsigned int d);
	void setDate(unsigned int y, unsigned int m, unsigned int d);
	void setstringDate(string date);
	unsigned int getYear() const;
	unsigned int getMonth() const;
	unsigned int getDay() const;
	unsigned int getTodayDay();
	unsigned int getTodayMonth();
	unsigned int getTodayYear();
	bool isValid();
	void Validate();
	bool operator==(const Date& rhs);
	bool operator>(const Date& rhs);
	bool operator>=(const Date& rhs);
	bool isLeapYear(int year);
	//===========================================NOT DONE===========================================
	string getStr(); // get (return) date as a string
	void save(ofstream & out) const;
	//===========================================NOT DONE===========================================
	friend ostream& operator<<(ostream& out, const Date & data);
	void show();

private: // PRIVATE data & function members are hidden from the user
	unsigned int year; // data member
	unsigned int month;
	unsigned int day;
	bool validDay;
	bool validMonth;
	bool validYear;
	bool valid = isValid();
};