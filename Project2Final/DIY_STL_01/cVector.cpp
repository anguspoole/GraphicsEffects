#include "cVector.h"

cVector::cVector()
{
	// Set up init data
		
	//static const unsigned int INIT_CAPACITY = 3;

	this->m_curCapacity = cVector::INIT_CAPACITY;
	
	// Allocate the array
	this->m_pMyData = new sPerson[this->m_curCapacity];


	this->m_nextIndex = 0;		// Initial insert index location

	return;
}

//static
unsigned int cVector::INIT_CAPACITY = 3;

cVector::~cVector()
{
	delete [] this->m_pMyData;

	return;
}

unsigned int cVector::GetSize(void)
{
	return this->m_nextIndex;
}



void cVector::InsertPersonAtEnd(sPerson person)
{
	this->m_pMyData[this->m_nextIndex] = person;

	// Move to the "next" location
	this->m_nextIndex++;			// 3

	// Check to see if I've exceeded the capacity of the array
	if ( this->m_nextIndex >= this->m_curCapacity )
	{
		// Calculate new size
		this->m_curCapacity *= 2;		// 6  3

		// Make a new array 
		sPerson* pNewArray = new sPerson[this->m_curCapacity];		// 6 in size

		// Copy the old data into the new one
		for ( unsigned int index = 0; index < this->m_nextIndex; index++ )
		{
			pNewArray[index] = this->m_pMyData[index];
		}

		// Delete the old one
		delete [] this->m_pMyData;			// Bye, bye

		// Point the array to the new location
		this->m_pMyData = pNewArray;
	}

	return;
}

void cVector::InsertPersonAtIndex(unsigned int index, sPerson person)
{
	// TODO:
	return;
}


bool cVector::GetPersonAtIndex(unsigned int index, sPerson &thePerson)
{
	thePerson = this->m_pMyData[index];
	return true;
}


