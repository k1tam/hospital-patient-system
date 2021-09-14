/* 
Module			: PreTriage
Filename        : PreTriage.cpp
Version         : 1.0
Author	        : Kelvin Tam
*/
#include <iostream>
#include <fstream>
#include "PreTriage.h"
#include "utils.h"
#include "Time.h"
#include "Patient.h"
#include "CovidPatient.h"
#include "TriagePatient.h"

using namespace std;

namespace sdds {

	// PreTriage Constructor, use Cstring for filename, initialize Time & Menu objects
	PreTriage::PreTriage(const char* dataFilename)
		: m_averCovidWait(15),
		m_averTriageWait(5),
		m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
		m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		if (dataFilename != nullptr)
		{
			m_dataFilename = new char[strLen(dataFilename) + 1];
			strCpy(m_dataFilename, dataFilename);
		}

		// call load function
		load();
	}

	// PreTriage Destructor
	PreTriage::~PreTriage()
	{
		// output data to external file
		ofstream fout(m_dataFilename);
		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << m_averCovidWait << endl;
		cout << "   Triage: " << m_averTriageWait << endl;
		fout << m_averCovidWait << "," << m_averTriageWait << endl;
		cout << "Saving m_lineup..." << endl;
		for (int i = 0; i < m_lineupSize; i++)
		{
			cout << i + 1 << "- ";
			m_lineup[i]->csvWrite(cout);
			cout << endl;
			m_lineup[i]->csvWrite(fout);
			fout << endl;
		}
		cout << "done!" << endl;
		delete[] m_dataFilename; // deallocate m_dataFilename memory
		for (int i = 0; i < maxNoOfPatients; i++)
		{
			delete m_lineup[i]; // deallocate array of patient pointers
		}
	}

	// Return the total estimated wait time for a type of patient 
	const Time PreTriage::getWaitTime(const Patient& p)const
	{
		int counter = 0;
		Time temp; // temporary Time object

		for (int i = 1; i < m_lineupSize; i++)
		{
			if (p.number() != m_lineup[i]->number() && p.type() == m_lineup[i]->type())
			{
				counter++;
			}
		}
		if (p.type() == 'T')
		{
			temp = counter * int(m_averTriageWait);
		}
		else if (p.type() == 'C')
		{
			temp = counter * int(m_averCovidWait);
		}

		return temp;
	}

	// Adjust type of patient's average wait time on admittance time of patient
	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		Time CT;				// Current Time
		Time PTT = (Time)(p);	// Patient Ticket Time
		Time AWT;				// Average wait time (covid or triage)
		unsigned int PTN = p.number(); // Patient's Ticket Number

		if (p.type() == 'C')
		{
			AWT = (unsigned int)(m_averCovidWait);
		}
		else if (p.type() == 'T')
		{
			AWT = (unsigned int)(m_averTriageWait);
		}

		// AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN
		AWT = ((CT.setToNow() - PTT) + (AWT * (PTN - 1))) / PTN;
		if (p.type() == 'C')
		{
			m_averCovidWait = AWT;
		}
		if (p.type() == 'T')
		{
			m_averTriageWait = AWT;
		}
	}

	// Remove a patient from lineup & memory using removeDynamicElement template
	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	// Finds index of the first patient in line that matches the type argument
	int PreTriage::indexOfFirstInLine(char type) const
	{
		int indexFinder = -1;
		int foundFlag = 0;
		for (int i = 0; i < m_lineupSize && !foundFlag; i++)
		{
			if (m_lineup[i]->type() == type)
			{
				indexFinder = i; // save the index
				foundFlag = 1;
			}
		}
		return indexFinder;
	}

	// Load average wait times & patient record from data file
	void PreTriage::load()
	{
		ifstream fin;
		int i = 0;
		char patientType;
		Patient* temp = nullptr;

		// open data file
		fin.open(m_dataFilename);
		cout << "Loading data..." << endl;
		if (fin.is_open() && fin.good()) // if successful
		{
			fin >> m_averCovidWait;
			fin.ignore(1000, ','); // ignore comma
			fin >> m_averTriageWait;
			fin.ignore(1000, '\n'); // ignore newline
			if (!fin.eof())
			{
				for (i = 0; i < maxNoOfPatients ; i++) 
				{
					patientType = '\0';
					fin >> patientType;
					if (patientType != '\0') // if patient type is read with no proper char, skip this
					{
						if (patientType == 'C')
						{
							temp = new CovidPatient();
						}
						else if (patientType == 'T')
						{
							temp = new TriagePatient();
						}
						if (temp) // if the object has been created successfully 
						{
							fin.ignore(1000, ','); // ignore comma
							temp->fileIO(true);
							temp->csvRead(fin);
							temp->fileIO(false);
							m_lineup[m_lineupSize++] = temp;
						}
					}
				}
				if (fin) //if (i > maxNoOfPatients)
				{
					cout << "Warning: number of records exceeded 100" << endl;
				}
			}
			else // if file is empty
			{
				cout << "No data or bad data file!" << endl;
			}
		}
		if (m_lineupSize > 0)
		{
			// output the amount of records imported
			cout << m_lineupSize << " Records imported..." << endl;
		}
		cout << endl;
		// close and clear file
		fin.clear();
		fin.close();
	}

	// Register a new patient
	void PreTriage::reg()
	{
		int selection;
		bool fullLine = false;
		bool success = false;
		Time temp;
		if (m_lineupSize == maxNoOfPatients)
		{
			// output following if lineup is full
			cout << "Line up full!" << endl;
			fullLine = true;
		}
		while (!success && !fullLine && m_pMenu >> selection)
		{
			switch (selection)
			{
			case 0: // Terminate Function
				break;
			case 1:
				// Instantiate CovidPatient
				m_lineup[m_lineupSize] = new CovidPatient();
				break;
			case 2:
				// Instantiate TriagePatient
				m_lineup[m_lineupSize] = new TriagePatient();
				break;
			}
			// get all patient info
			m_lineup[m_lineupSize]->setArrivalTime();
			cout << "Please enter patient information: " << endl;
			m_lineup[m_lineupSize]->fileIO(false);
			m_lineup[m_lineupSize]->read(cin);
			cout << endl;

			// Print Patient Info
			cout << "******************************************" << endl;
			m_lineup[m_lineupSize]->write(cout);
			cout << "Estimated Wait Time: ";
			getWaitTime(*m_lineup[m_lineupSize]).write(cout);
			cout << endl << "******************************************" << endl << endl;
			m_lineupSize++; // increment line up size
			success = true;
		}
	}

	// Calls next patient in line to be admitted to the covid or triage center
	void PreTriage::admit()
	{
		int selection;
		int indexFound = 0;
		m_pMenu >> selection; // menu selection & validation
		switch (selection)
		{
		case 0:
			break;
		case 1:
			// Type is C
			indexFound = indexOfFirstInLine('C');
			break;
		case 2:
			// Type is T
			indexFound = indexOfFirstInLine('T');
			break;
		}
		if (indexFound != -1 && selection > 0) // if patient is found 
		{
			cout << endl << "******************************************" << endl;
			m_lineup[indexFound]->fileIO(false);
			cout << "Calling for ";
			m_lineup[indexFound]->write(cout); // output the next patient info
			cout << "******************************************" << endl << endl;
			setAverageWaitTime(*m_lineup[indexFound]); // set avg wait time
			removePatientFromLineup(indexFound); // remove patient after admitted
		}
	}

	void PreTriage::run()
	{
		int selection;
		while (m_appMenu >> selection)
		{
			switch (selection)
			{
			case 0:
				break;
			case 1:
				reg();		// register patient
				break;
			case 2:
				admit();	// admit patient
				break;
			}
		}
	}
}