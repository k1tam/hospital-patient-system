/* 
Module			: Patient
Filename        : Patient.cpp
Version         : 1.0
Author	        : Kelvin Tam
*/
#include <iostream>
#include <string>
#include <cstring>
#include "IOAble.h"
#include "Ticket.h"
#include "Patient.h"
#include "Time.h"
#include "utils.h"

using namespace std;

namespace sdds {

	// Patient Constructor with two parameters
	Patient::Patient(int ticketNum, bool flag) : m_ticket(ticketNum)
	{
		m_name = nullptr;
		m_ohip = 0;
		ioFlag = flag;
	}
	
	// Patient Destructor, deallocates patient name memory 
	Patient::~Patient()
	{
		delete[] m_name; // deallocate memory for m_name
		m_name = nullptr;
	}

	// Returns the member of file IO Flag
	bool Patient::fileIO() const
	{
		return ioFlag;
	}

	// Receives a boolean value to set the member fileIO flag
	void Patient::fileIO(bool flag)
	{
		ioFlag = flag;
	}

	// Compare current object with incoming single character 
	// Return boolean based on matching type() char & single
	bool Patient::operator==(const char single) const
	{
		bool charReturn = false;
		if (single == type())
		{
			charReturn = true;
		}
		return charReturn;
	}

	// Compare current object with another patient
	// Return boolean based on matching patient
	bool Patient::operator==(const Patient& src) const
	{
		bool patientMatch = false;
		if (type() == src.type())
		{
			patientMatch = true;
		}
		return patientMatch;
	}

	// Sets the time of the ticket of patient to current time
	void Patient::setArrivalTime() 
	{
		m_ticket.resetTime(); // reset time using resetTime() from Ticket module
	}

	// Cast patient to Time type, returns time of the ticket
	Patient::operator Time() const
	{
		return Time(m_ticket);
	}

	// Returns number of the ticket
	int Patient::number() const
	{
		return m_ticket.number();
	}

	// csvWrite function overwrite. Insert type value, patient name, ohip number
	std::ostream& Patient::csvWrite(std::ostream& ostr) const
	{
		// output patient name & OHIP num
		ostr << type() << "," << m_name << "," << m_ohip << ","; 
		m_ticket.csvWrite(ostr); // output ticket info
		return ostr;
	}

	// csvRead function overwrite. Extract name, ohip number, ticket object
	std::istream& Patient::csvRead(std::istream& istr)
	{
		// Patient Name
		delete[] m_name; // deallocate memory for m_name
		m_name= getcstr("", istr, ','); // input patient name 

		// Ohip Number
		istr >> m_ohip; // input OHIP number
			
		istr.ignore(1000, ','); // ignore comma

		// Ticket Object
		m_ticket.csvRead(istr); // input ticket info

		return istr;
	}

	// Insert patient information into ostream, displayed on the console
	std::ostream& Patient::write(std::ostream& ostr) const
	{
		m_ticket.write(ostr); // output ticket info
		ostr << endl;
		if (strLen(m_name) > 25) // count the char length of m_name
		{
			for (int i = 0; i < 25; i++) 
			{
				ostr << m_name[i]; // output m_name (25 chars ONLY)
			}
		}
		else
		{
			ostr << m_name; // output m_name
		}
		ostr << ", OHIP: " << m_ohip; // output OHIP num 
		return ostr;
	}

	// Extract Ticket information from the console using istream
	std::istream& Patient::read(std::istream& istr)
	{
		delete[] m_name; // deallocate memory for m_name
		// input m_name
		m_name= getcstr("Name: ", istr, '\n'); 
		// input OHIP num
		m_ohip = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true); 
		return istr;
	}
}