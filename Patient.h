/* 
Module			: Patient
Filename        : Patient.h
Version         : 1.0
Author	        : Kelvin Tam
*/

#ifndef SDDS_PATIENT_H
#define SDDS_PATIENT_H
#include "IOAble.h"
#include "Ticket.h"

namespace sdds {
	class Patient : public IOAble {
		char* m_name;
		int m_ohip;
		Ticket m_ticket; 
		bool ioFlag;
	public:

		// Patient Constructor with two parameters
		Patient(int ticketNum = 0, bool flag = false);

		// Patient Destructor, deallocates patient name memory 
		~Patient();

		// Copy Constructor 
		Patient(const Patient& src) = delete;

		// Copy Assignment
		Patient& operator=(const Patient& src) = delete;

		// Returns a characer to identify the type of patient
		virtual char type()const = 0;

		// Returns the member of file IO Flag
		bool fileIO() const;

		// Receives a boolean value to set the member fileIO flag
		void fileIO(bool flag);

		// Compare current object with incoming single character 
		// Return boolean based on matching type() char & single
		bool operator==(const char single) const;

		// Compare current object with another patient
		// Return boolean based on matching patient
		bool operator==(const Patient& src) const;
			
		// Sets the time of the ticket of patient to current time
		void setArrivalTime();

		// Cast patient to Time type, returns time of the ticket
		operator Time() const;

		// Returns number of the ticket
		int number() const;

		// csvWrite function overwrite. Insert type value, patient name, ohip number
		std::ostream& csvWrite(std::ostream& ostr) const;

		// csvRead function overwrite. Extract name, ohip number, ticket object
		std::istream& csvRead(std::istream& istr);

		// Insert patient information into ostream, displayed on the console
		std::ostream& write(std::ostream& ostr) const;

		// Extract Ticket information from the console using istream
		std::istream& read(std::istream& istr);
 	};

}
#endif // !SDDS_PATIENT_H
