/* 
Module			: CovidPatient
Filename        : CovidPatient.cpp
Version         : 1.0
Author	        : Kelvin Tam
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Ticket.h"
#include "CovidPatient.h"

using namespace std;

namespace sdds {
	int nextCovidTicket = 1;

	// Default CovidPatient Constructor
	CovidPatient::CovidPatient() : Patient(nextCovidTicket)
	{
		nextCovidTicket++;
	}

	// Identify patient object as covid patient, return letter C
	char CovidPatient::type() const
	{
		return 'C';
	}

	// csvRead virtual function override
	std::istream& CovidPatient::csvRead(std::istream& istr)
	{
		Patient::csvRead(istr); // output patient info using base class csvRead()
		nextCovidTicket = Patient::number() + 1; // increment ticket num
		istr.ignore(1000, '\n'); // ignore newline
		return istr;
	}

	// csvWrite virtual function override
	std::ostream& CovidPatient::write(std::ostream& ostr) const
	{
		if (Patient::fileIO())
		{
			// output patient info using base class csvWrite() 
			Patient::csvWrite(ostr); 
		}
		else
		{
			// output patient info using base class write()
			ostr << "COVID TEST" << endl;
			Patient::write(ostr); 
			ostr << endl;
		}
		return ostr;
	}

	// read virtual function override
	std::istream& CovidPatient::read(std::istream& istr)
	{
		if (Patient::fileIO())
		{
			// input covid patient info
			csvRead(istr);
		}
		else
		{
			// input patient info using base class read()
			Patient::read(istr);
		}
		return istr;
	}

}