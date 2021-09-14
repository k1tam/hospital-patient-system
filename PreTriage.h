/* 
Module			: PreTriage
Filename        : PreTriage.h
Version         : 1.0
Author	        : Kelvin Tam

*/


#ifndef SDDS_PRETRIAGE_H
#define SDDS_PRETRIAGE_H
#include "Time.h"
#include "Patient.h"
#include "Menu.h"

namespace sdds {

	const int maxNoOfPatients = 100; // Set the max num of patients in the lineup (covid AND triage)

	class PreTriage {

		// Time object, hold avg wait time for covid test and triage per patient
		Time 
			m_averCovidWait, 
			m_averTriageWait;

		// Array of Patient pointers, hold covid & triage patient lineups dynamically
		Patient* m_lineup[maxNoOfPatients]{};
		
		// Character pointer, hold name of the data file dynamically
		char* m_dataFilename = nullptr;

		// Number of patients in lineup
		int m_lineupSize = 0;
		
		// Menu object
		Menu
			// hold the main menu
			m_appMenu,
			// hold the covid/triage patient selection
			m_pMenu	;


		// Register a new patient
		void reg();

		// Calls next patient in line to be admitted to the covid or triage center
		void admit();

		// Return the total estimated wait time for a type of patient 
		const Time getWaitTime(const Patient& p)const;

		// Adjust type of patient's average wait time on admittance time of patient
		void setAverageWaitTime(const Patient& p);

		// Remove a patient from lineup & memory using removeDynamicElement template
		void removePatientFromLineup(int index);

		// Finds index of the first patient in line that matches the type argument
		int indexOfFirstInLine(char type) const;
		
		// Load average wait times & patient record from data file
		void load();
	public:
		// PreTriage Constructor, use Cstring for filename, initialize Time & Menu objects
		PreTriage(const char* dataFilename);

		// PreTriage Destructor
		~PreTriage();
		
		void run(void);
	};
}
#endif // !SDDS_PRETRIAGE_H
