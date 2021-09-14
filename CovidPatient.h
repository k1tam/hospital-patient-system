/* 
Module			: CovidPatient
Filename        : CovidPatient.h
Version         : 1.0
Author	        : Kelvin Tam

*/

#ifndef SDDS_COVIDPATIENT_H
#define SDDS_COVIDPATIENT_H
#include "Patient.h"

namespace sdds {
	class CovidPatient : public Patient {
	public:
		// Default CovidPatient Constructor
		CovidPatient();

		// Identify patient object as covid patient, return letter C
		virtual char type() const;

		// csvRead virtual function override
		std::istream& csvRead(std::istream& istr);

		// write virtual function override
		std::ostream& write(std::ostream& ostr) const;

		// read virtual function override
		std::istream& read(std::istream& istr);
	};
}

#endif // !SDDS_COVIDPATIENT_H


