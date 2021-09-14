/* 
Module			: Ticket
Filename        : Ticket.cpp
Version         : 1.0
Author	        : Kelvin Tam

*/

#include <iostream>
#include "Ticket.h"

using namespace std;

namespace sdds {

	// Ticket Constructor, set m_number to argument parameter 
	Ticket::Ticket(int number) {
		m_number = number;
	}
	
	// Cast Ticket to Time, return m_time
	Ticket::operator Time() const {
		return m_time;
	}

	// Query returns ticket number
	int Ticket::number() const {
		return m_number;
	}

	// Set Ticket time to current time
	void Ticket::resetTime() {
		m_time.setToNow(); // call setToNow() from Time module
	}

	// Insert comma-separated Ticket number & time into ostream
	std::ostream& Ticket::csvWrite(std::ostream& ostr) const {
		// output ticket number and time
		return ostr << m_number << "," << m_time;  
	}

	// Extract Ticket number and Time into comma-separated format from istream
	std::istream& Ticket::csvRead(std::istream& istr) {
		istr >> m_number; // input ticket number
		istr.ignore(1000, ','); // ignore comma
		return istr >> m_time;
	}

	// Insert Ticket into ostream, displayed on console
	std::ostream& Ticket::write(std::ostream& ostr) const {
		// output and return ticket number and time
		return ostr << "Ticket No: " << m_number << ", Issued at: " << m_time;
	}

	// Extract ticket information from istream
	std::istream& Ticket::read(std::istream& istr) {
		// input ticket info
		return csvRead(istr); 
	}
}
