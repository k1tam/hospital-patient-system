/* 
Module			: TriagePatient
Filename        : TriagePatient.h
Version         : 1.0
Author	        : Kelvin Tam
*/

#include "Patient.h"
#include "Ticket.h"
#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
namespace sdds {

	class TriagePatient : public Patient {
		char* symptom;
	public:
		// Default TriagePatient Constructor
		TriagePatient();

		// Identifies patient as triage patient, return letter T
		virtual char type() const;

		// csvWrite virtual function override
		std::ostream& csvWrite(std::ostream& ostr) const;

		// csvRead virtual function override
		std::istream& csvRead(std::istream& istr);

		// write virtual function override
		std::ostream& write(std::ostream& ostr) const;

		// read virtual function override
		std::istream& read(std::istream& istr);

		// TriagePatient Destructor, deallocate symptom memory
		~TriagePatient();
	};
}
#endif // !SDDS_TRIAGEPATIENT_H


