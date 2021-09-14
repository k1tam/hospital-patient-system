/* 
Module			: Time
Filename        : Time.cpp
Version         : 1.0
Author	        : Kelvin Tam
*/

#include <string>
#include <math.h>
#include "Time.h"
#include "utils.h"

using namespace std;
namespace sdds {
	// Set the time to current time using getTime function
	Time& Time::setToNow()
	{
		m_min = getTime(); // call getTime() from utils module
		return *this;
	}

	// Constructor for class Time, default m_min to 0
	Time::Time(unsigned int min)
	{
		m_min = 0;
		if (min >= 0)
		{
			m_min = min;
		}
	}

	// Write time into a stream in HH:MM format
	ostream& Time::write(std::ostream& ostr) const
	{
		int hour = m_min / 60;
		int min = m_min % 60;

		// Printing Hours
		ostr.fill('0');
		ostr.width(2);
		ostr << hour << ":"; // output hours num & colon symbol
		// Printing Minutes
		ostr.width(2);
		ostr << min; // output min num

		return ostr;
	}


	// Read time from a stream in H:M format with input validation
	// Where two integers are greater than 0 and separated by a colon
	istream& Time::read(std::istream& istr)
	{
		char colon;
		int hour, min;
		hour = min = 0;
		istr >> hour; // input hour num
		istr.get(colon); // input colon
		istr >> min; // input min num

		// set failbit if input is not the right type OR format
		if (istr.fail() || hour < 0 || colon != ':' || min < 0) 
		{
			istr.setstate(ios::failbit);
		}
		else {
			m_min = (hour * 60) + min; // convert input format to minutes 
		}

		return istr;
	}

	// Time subtraction (m_min), turning a 24 hour clock backwards
	Time& Time::operator-=(const Time& D)
	{
		double days = 1.00;
		if (m_min < D.m_min)
		{
			if (D.m_min > 1440)
			{
				// convert the amount of minutes to days
				days = (double(D.m_min) / 60) / 24; 
				days = round(days);
			}
			m_min += 1440 * days;
		}
		m_min -= D.m_min;
		return *this;
	}

	// Time subtraction (m_min), turning a 24 hour clock backwards
	// No side-effects
	Time Time::operator-(const Time& D) const
	{
		Time temp;
		double days = 1.00;

		if (m_min < D.m_min)
		{
			if (D.m_min > 1440)
			{
				days = (double(D.m_min) / 60) / 24;
				days = round(days);
			}
			temp.m_min += 1440 * int(days);
		}
		temp.m_min += (m_min - D.m_min);
		return temp;
	}

	// Time addition (m_min), add left value to the minute value on the right
	Time& Time::operator+=(const Time& D)
	{
		m_min += D.m_min;
		return *this;
	}

	// Create Time object that sums the left and right minute value 
	// into the minute value within
	Time Time::operator+(const Time& D) const
	{
		Time temp; // temporary time object
		temp.m_min = m_min + D.m_min;
		return temp;
	}

	// Set the minute value of left operand to the right value
	//  return the reference of the left operand
	Time& Time::operator=(unsigned int val)
	{
		m_min = val;
		return *this;
	}

	// Multiply left minute value by the right value
	// return the reference of the left operand
	Time& Time::operator*= (unsigned int val)
	{
		m_min *= val;
		return *this;
	}

	// Divides minutes value of left value by the right value
	// return the reference of the left operand
	Time& Time::operator/= (unsigned int val)
	{
		m_min /= val;
		return *this;
	}

	// Create Time object with minute value being the product of the 
	// left value multiply to the right value, returns object
	Time Time::operator* (unsigned int val) const
	{
		Time temp; // temporary time object
		temp.m_min = m_min * val;
		return temp;
	}

	// Create Time object with minute value being the division of 
	// left value by the right value, returns object
	Time Time::operator/(unsigned int val) const
	{
		Time temp; // temporary time object
		temp.m_min = m_min / val;
		return temp;
	}

	// Cast Time to an integer, returns the number of minutes as int
	Time::operator unsigned int() const
	{
		return m_min;
	}

	// Cast Time to unsigned integer, return the number of minutes
	Time::operator int() const
	{
		return int(m_min);
	}

	// Insert a Time object into an ostream object
	ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		D.write(ostr);
		return ostr;
	}

	// Extract data from an istream object into the Time object
	istream& operator>>(std::istream& istr, Time& D)
	{
		D.read(istr);
		return istr;
	}

}