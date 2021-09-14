/*
Module			: utils
Filename        : utils.cpp
Version         : 1.0
Author	        : Kelvin Tam

*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {


	// making sdds::debug variable global to all the files
	// which include: "utils.h"
	bool debug = false;  // made global in utils.h

	// performs a fool-proof integer entry from the console
	int getInt(const char* prompt) {

		int userInput, invalidFlag = 0;
		if (prompt) {
			cout << prompt; // display prompt if provided
		}
		do {
			cin >> userInput; // extract from istream
			if (cin.fail())
			{
				cerr << "Bad integer value, try again: ";
				// clear & ignore input
				cin.clear();
				cin.ignore(2000, '\n');
			}
			else if (char(cin.get()) != '\n')
			{
				cerr << "Enter only an integer, try again: ";
				// clear & ignore input
				cin.clear();
				cin.ignore(2000, '\n'); 
			}
			else
			{
				invalidFlag = 1;
			}
		} while (!invalidFlag);

		return userInput;
	}

	// Performs a fool-proof integer entry from console with additional features
	int getInt(int min, int max, const char* prompt,
		const char* errorMessage, bool showRangeAtError)
	{
		int userInput=0, invalidFlag = 0;
		char newLine;
		if (prompt != nullptr) {
			cout << prompt;
		}

		do {

			cin >> userInput; // extract from istream
			cin.get(newLine); 
			if (cin.fail()) // fails if input is not an int
			{
				cerr << "Bad integer value, try again: ";
				cin.clear();
				cin.ignore(2000, '\n');
				invalidFlag = 0;
			}
			else if (newLine != '\n')
			{
				cerr << "Enter only an integer, try again: ";
				cin.clear();
				cin.ignore(2000, '\n');
				invalidFlag = 0;
			}
			// If userinput is an int but not within the range
			else if ((userInput < min || userInput > max))
			{
				if (errorMessage) {
					cerr << errorMessage;
				}
				if (showRangeAtError) {
					cerr << "[" << min << " <= value <= " << max << "]: ";
				}
				invalidFlag = 0;
			}
			else
			{
				invalidFlag = 1;
			}
		} while (!invalidFlag);

		return userInput;
	}

	// Prompt user to enter an unknown size string, allocate memory to the string and copy value 
	char* getcstr(const char* prompt, std::istream& istr, char delimiter)
	{
		string strObj; // temporary string object
		char* allocated = nullptr;
		if (prompt) 
		{
			cout << prompt; // display prompt if provided
		}
		getline(istr, strObj, delimiter); // takes the input stream into strObj
		delete[] allocated;
		allocated = new char[strObj.length() + 1];
		strCpy(allocated, strObj.c_str()); // change strObj into a C string

		return allocated;
	}

	// returns the time of day in minutes
	int getTime() {
		int mins = -1;
		if (debug) {
			Time t(0);
			cout << "Enter current time: ";
			do {
				cin.clear();
				cin >> t;   // needs extraction operator overloaded for Time
				if (!cin) {
					cout << "Invlid time, try agian (HH:MM): ";
					cin.clear();
				}
				else {
					mins = int(t);
				}
				cin.ignore(1000, '\n');
			} while (mins < 0);
		}
		else {
			time_t t = time(NULL);
			tm lt = *localtime(&t);
			mins = lt.tm_hour * 60 + lt.tm_min;
		}
		return mins;
	}

	// Copies the srouce character string into the destination
	void strCpy(char* des, const char* src)
	{
		int i;

		for (i = 0; src[i] != '\0'; i++)
		{
			des[i] = src[i];
		}
		des[i] = '\0';
	}

	// Copies the source character string into the destination upto "len"
	// characters. The destination will be null terminated only if the number
	// of the characters copied is less than "len"
	void strnCpy(char* des, const char* src, int len)
	{
		int i, charCount = 0;

		for (i = 0; src[i] != '\0' && i < len; i++)
		{
			des[i] = src[i];
			charCount++;
		}

		if (charCount < len)
		{
			des[charCount] = '\0';
		}
	}

	// Compares two C-strings 
	// returns 0 i thare the same
	// return > 0 if s1 > s2
	// return < 0 if s1 < s2
	int strCmp(const char* s1, const char* s2)
	{
		int i;
		char a, b;

		for (i = 0; s1[i] != '\0' && s1[i] == s2[i]; i++);

		a = s1[i];
		b = s2[i];

		return (a < b) ? -1 : (a == b) ? 0 : 1;
	}

	// returns 0 i thare the same
	// return > 0 if s1 > s2
	// return < 0 if s1 < s2
	int strnCmp(const char* s1, const char* s2, int len)
	{
		int i;
		char a, b;

		for (i = 0; i < len - 1 && s1[i] == s2[i]; i++);

		a = s1[i];
		b = s2[i];

		return (a < b) ? -1 : (a == b) ? 0 : 1;
	}

	// returns the lenght of the C-string in characters
	int strLen(const char* s)
	{
		int i, counter = 0;

		for (i = 0; s[i] != '\0'; i++)
		{
			counter++;
		}
		return counter;
	}

	// returns the address of first occurance of "str2" in "str1"
	// returns nullptr if no match is found
	const char* strStr(const char* str1, const char* str2)
	{
		int i, lenCount, match, flag, location;
		lenCount = match = flag = 0;

		lenCount = strLen(str2);

		for (i = 0; str1[i] != '\0' && !flag; i++)
		{
			if (str2[0] == str1[i])
			{
				match = strnCmp(&str1[i], str2, lenCount);
				if (!match)
				{
					flag = 1;
					location = i;
				}
			}
		}
		return (!match) ? &str1[location] : nullptr;
	}

	// Concantinates "src" C-string to the end of "des"
	void strCat(char* des, const char* src)
	{
		int lastPos;
		lastPos = strLen(des);
		strCpy(&des[lastPos], src);
	}

}