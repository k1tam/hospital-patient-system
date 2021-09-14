/* 
Module			: Menu
Filename        : Menu.h
Version         : 1.0
Author	        : Kelvin Tam
*/

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {

	class Menu {
		char* m_text; // holds the menu content dynamically 
		int m_noOfSel; // holds the number of options displayed in menu content

		// Menu display function, displays menu choices
		void display() const;
	public:

		// Menu Constructor with two parameters
		Menu(const char* MenuContent, int NoOfSelections);

		// Menu destructor, deallocates memory 
		virtual ~Menu();

		// Insertion operator function, validate input between 0 and m_noOfSel
		int& operator>>(int& Selection);
		
		// add safe copying logic

		// Menu copy constructor
		Menu(const Menu&);

		// Menu copy assignment operator 
		Menu& operator=(const Menu&);
	};
}
#endif // !SDDS_MENU_H
