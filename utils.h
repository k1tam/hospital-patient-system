/* 
Module			: utils
Filename        : utils.h
Version         : 1.0
Author	        : Kelvin Tam
*/

#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_
#include <iostream>
namespace sdds {

	// Remove Patient from the lineup wen admitted
	template <typename type>
	void removeDynamicElement(type* array[], int index, int& size) {
		delete array[index];
		for (int j = index; j < size; j++) {
			array[j] = array[j + 1];
		}
		size--;
	}

	// making sdds::debug variable global to all the files
	// which include: "utils.h"
	extern bool debug;

	// performs a fool-proof integer entry from the console
	int getInt(const char* prompt = nullptr);

	// Performs a fool-proof integer entry from console with additional features
	int getInt(int min, int max, const char* prompt = nullptr,
		const char* errorMessage = nullptr,
		bool showRangeAtError = true);

	// returns the time of day in minutes
	int getTime();


	// Prompt user to enter an unknown size string, allocate memory to the string and copy value 
	char* getcstr(const char* prompt = nullptr,
		std::istream& istr = std::cin,
		char delimiter = '\n');

	// Copies the srouce character string into the destination
	void strCpy(char* des, const char* src);

	// Copies the source character string into the destination upto "len"
	// characters. The destination will be null terminated only if the number
	// of the characters copied is less than "len"
	void strnCpy(char* des, const char* src, int len);

	// Compares two C-strings 
	// returns 0 i thare the same
	// return > 0 if s1 > s2
	// return < 0 if s1 < s2
	int strCmp(const char* s1, const char* s2);

	// returns 0 i thare the same
	// return > 0 if s1 > s2
	// return < 0 if s1 < s2
	int strnCmp(const char* s1, const char* s2, int len);

	// returns the lenght of the C-string in characters
	int strLen(const char* s);

	// returns the address of first occurance of "str2" in "str1"
	// returns nullptr if no match is found
	const char* strStr(const char* str1, const char* str2);

	// Concantinates "src" C-string to the end of "des"
	void strCat(char* des, const char* src);

}
#endif // !SDDS_UTILS_H_

