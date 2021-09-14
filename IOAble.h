/* 
Module			: IOAble
Filename        : IOAble.h
Version         : 1.0
Author	        : Kelvin Tam
*/

#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H
#include <iostream> 

namespace sdds
{
	class IOAble {
	public:

		// Receives reference of ostream and returns reference of ostream, incapable of changing current object
		// For future comma-separated ostream outputs
		virtual std::ostream& csvWrite(std::ostream& ostr)const = 0;

		// Receives reference of istream and returns reference of istreams
		// For future comma-separated istream outputs
		virtual std::istream& csvRead(std::istream& istr) = 0;

		// Receives reference of ostream and returns reference of ostream, incapable of changing current object
		//For future ostream outputs
		virtual std::ostream& write(std::ostream& ostr)const = 0;

		// Receives reference of istream and returns reference of istreams
		//For future istream outputs
		virtual std::istream& read(std::istream& istr) = 0;

		// Virtual IOAble destructor
		virtual ~IOAble();
	};

	// Overloaded insertion operator function for IOAble Object
	std::ostream& operator<<(std::ostream&, const IOAble& i);

	// Overloaded extraction operator function for IOAble Object
	std::istream& operator>>(std::istream&, IOAble& i);
}

#endif // !SDDS_IOABLE_H
