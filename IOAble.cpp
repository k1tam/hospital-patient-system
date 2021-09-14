/*
Module			: IOAble
Filename        : IOAble.cpp
Version         : 1.0
Author	        : Kelvin Tam
*/

#include <iostream>
#include "IOAble.h"
using namespace std;

namespace sdds {

	// Virtual IOAble destructor
	IOAble::~IOAble() {};

	// Overloaded insertion operator function for IOAble Object
	std::ostream& operator<<(std::ostream& os, const IOAble& i)
	{
		i.write(os);
		return os;
	}

	// Overloaded extraction operator function for IOAble Object
	std::istream& operator>>(std::istream& is, IOAble& i)
	{
		i.read(is);
		return is;
	}

}