/* 
Module			: Menu
Filename        : Menu.cpp
Version         : 1.0
Author	        : Kelvin Tam
*/
#include <iostream>
#include <string>
#include "Menu.h"
#include "utils.h"

using namespace std;

namespace sdds {

	// Menu Constructor with two parameters
	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{
		m_text = nullptr;
		m_noOfSel = 0;
		if (MenuContent != nullptr)
		{
			m_text = new char[strLen(MenuContent)+1];
			strCpy(m_text, MenuContent);
		}

		if (NoOfSelections > 0)
		{
			m_noOfSel = NoOfSelections;
		}

	}

	// Menu destructor, deallocates memory 
	Menu::~Menu()
	{
		delete[] m_text;
		m_text = nullptr;
	}

	// Menu copy constructor
	Menu::Menu(const Menu& src)
	{
		m_noOfSel = src.m_noOfSel;

		if (src.m_text != nullptr)
		{
			m_text = new char[strLen(src.m_text) + 1];
			strCpy(m_text, src.m_text); // copy the menu text
		}
		else {
			m_text = nullptr;
		}
	}

	// Menu copy assignment operator 
	Menu& Menu::operator=(const Menu& src)
	{
		if (this != &src)
		{
			m_noOfSel = src.m_noOfSel;
			delete[] m_text; // deallocate memory for m_text
			if (src.m_text != nullptr)
			{
				m_text = new char[strLen(src.m_text) + 1];
				strCpy(m_text, src.m_text); // copy the menu text
			}
			else {
				m_text = nullptr;
			}

		}
		return *this;
	}

	// Menu display function, displays menu choices
	void Menu::display() const
	{
		cout << m_text << endl;
		cout << "0- Exit" << endl;
	}

	// Insertion operator function, validate input between 0 and m_noOfSel
	int& Menu::operator>>(int& Selection)
	{
		display();
		Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);

		return Selection;
	}

}