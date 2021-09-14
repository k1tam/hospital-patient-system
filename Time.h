/* 
Module			: Time
Filename        : Time.h
Version         : 1.0
Author	        : Kelvin Tam
ID				: 142280205

*/

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <iostream>
namespace sdds {
   class Time {
      unsigned int m_min;

   public:
       // Set the time to current time using getTime function
      Time& setToNow();

      // Constructor for class Time, default m_min to 0
      Time(unsigned int min = 0);

      // Write time into a stream in HH:MM format
      std::ostream& write(std::ostream& ostr) const;

      // Read time from a stream in H:M format with input validation
      // Where two integers are greater than 0 and separated by a colon
      std::istream& read(std::istream& istr);
      
      // Time subtraction (m_min), turning a 24 hour clock backwards
      Time& operator-=(const Time& D);

      // Time subtraction (m_min), turning a 24 hour clock backwards
      // No side-effects
      Time operator-(const Time& D)const;

      // Time addition (m_min), add left value to the minute value on the right
      Time& operator+=(const Time& D);

      // Create Time object that sums the left and right minute value 
      // into the minute value within
      Time operator+(const Time& D)const;

      // Set the minute value of left operand to the right value
      //  return the reference of the left operand
      Time& operator=(unsigned int val);

      // Multiply left minute value by the right value
      // return the reference of the left operand
      Time& operator *= (unsigned int val);

      // Divides minutes value of left value by the right value
      // return the reference of the left operand
      Time& operator /= (unsigned int val);

      // Create Time object with minute value being the product of the 
      // left value multiply to the right value, returns object
      Time operator *(unsigned int val)const;

      // Create Time object with minute value being the division of 
      // left value by the right value, returns object
      Time operator /(unsigned int val)const;

      // Cast Time to an integer, returns the number of minutes as int
      operator unsigned int()const;

      // Cast Time to unsigned integer, return the number of minutes
      operator int()const;
   };

   // Insert a Time object into an ostream object
   std::ostream& operator<<(std::ostream& ostr, const Time& D);

   // Extract data from an istream object into the Time object
   std::istream& operator>>(std::istream& istr, Time& D);
}

#endif // !SDDS_TIME_H

