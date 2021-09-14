/* Citation and Sources...
Final Project Milestone 5
Module			: Ticket
Filename        : Ticket.h
Version         : 1.0
Author	        : Kelvin Tam
ID				: 142280205
Email			: ktam27@myseneca.ca
Section			: NFF
Revision History
-----------------------------------------------------------
Date		Reason
2021/07/19  Preliminary release
2021/07/19  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#ifndef SDDS_TICKET_H_
#define SDDS_TICKET_H_
#include "Time.h"
#include "IOAble.h"
namespace sdds {
	class Ticket :public IOAble {
		Time m_time;
		int m_number=0;
	public:
		// Default Ticket Constructor
		Ticket(){}

		// Ticket Constructor, set m_number to argument parameter 
		Ticket(int number);

		// Cast Ticket to Time, return m_time
		operator Time()const;

		// Query returns ticket number
		int number()const;

		// Set Ticket time to current time
		void resetTime();

		// Insert comma-separated Ticket number & time into ostream
		std::ostream& csvWrite(std::ostream& ostr)const;

		// Extract Ticket number and Time into comma-separated format from istream
		std::istream& csvRead(std::istream& istr);

		// Insert Ticket into ostream, displayed on console
		std::ostream& write(std::ostream& ostr)const;

		// Extract ticket information from istream
		std::istream& read(std::istream& istr);
	};
}
#endif // !SDDS_TICKET_H_
