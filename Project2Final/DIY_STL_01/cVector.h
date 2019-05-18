#ifndef _DIYVector_HG_
#define _DIYVector_HG_

#include "cPerson.h"

class cVector
{
public:
	cVector();
	~cVector();

	void InsertPersonAtEnd(sPerson person);			// push_back()
	// Every single insert causes a "shift and copy" 
	// and also might cause a resize (and copy)
	void InsertPersonAtIndex(unsigned int index, sPerson person);
	bool GetPersonAtIndex(unsigned int index, sPerson &thePerson);		// operator[]

	void SetCapacity(unsigned int newCapacity);		// vec.reserve();

	unsigned int GetSize(void);		// Number of things in array
	unsigned int GetCapacity(void);	// Actual size of internal array

private:


	// Store data dynamically
	sPerson* m_pMyData;			// "array" of data


	// Vector can hold 3 things at the start
	static unsigned int INIT_CAPACITY;// = 3;
	unsigned int m_curCapacity;		// How big the array is
	unsigned int m_nextIndex;		// The "end" of the array
};

#endif

