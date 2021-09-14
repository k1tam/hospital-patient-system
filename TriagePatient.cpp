/* 
Module			: TriagePatient
Filename        : TriagePatient.cpp
Version         : 1.0
Author	        : Kelvin Tam
*/

#include <iostream>
#include <string>
#include "utils.h"
#include "TriagePatient.h"

using namespace std;

namespace sdds {
	int nextTriageTicket = 1;

	// Default TriagePatient Constructor
	TriagePatient::TriagePatient() : Patient(nextTriageTicket)
	{
		symptom = nullptr;
		nextTriageTicket++; // increment triage ticket num

	}

	// Identifies patient as triage patient, return letter T
	char TriagePatient::type() const
	{
		return 'T';
	}

	// csvWrite virtual function override
	std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const
	{
		Patient::csvWrite(ostr); // output patient info using base class csvWrite()
		ostr << ',' << symptom; // output triage patient symptoms 
		return ostr;
	}

	// csvRead virtual function override
	std::istream& TriagePatient::csvRead(std::istream& istr)
	{
		Patient::csvRead(istr); // input patient info using base class csvRead()
		istr.ignore(1000,','); // ignore comma
		delete[] symptom; // deallocate symptom memory
		symptom = getcstr("", istr, '\n'); // input symptom 
		nextTriageTicket = Patient::number() + 1; // increment triage ticket number
		return istr;
	}

	// write virtual function override
	std::ostream& TriagePatient::write(std::ostream& ostr) const
	{
		if (Patient::fileIO())
		{
			csvWrite(ostr); // output triage patient info
		}
		else
		{
			ostr << "TRIAGE" << endl;
			Patient::write(ostr); // output patient info using base class write()
			ostr << endl;
			ostr << "Symptoms: " << symptom << endl; // output patient symptoms 
		}
		return ostr;
	}

	// read virtual function override
	std::istream& TriagePatient::read(std::istream& istr)
	{
		if (Patient::fileIO())
		{
			csvRead(istr); // input triage patient info
		}
		else
		{
			delete[] symptom; // deallocate symptom memory
			Patient::read(istr); // input patient info using base class read()
			symptom = getcstr("Symptoms: ", istr, '\n'); // input patient symptoms
		}
		return istr;
	}

	// TriagePatient Destructor, deallocate symptom memory
	TriagePatient::~TriagePatient()
	{
		delete[] symptom; // deallocate symptom memory
		symptom = nullptr;
	}
}