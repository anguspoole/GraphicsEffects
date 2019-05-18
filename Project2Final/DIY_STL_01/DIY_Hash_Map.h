#ifndef _cHashMap_HG_
#define _cHashMap_HG_

#include "cPerson.h"
#include <string>

#include "cList.h"

class cHashMap
{
public:
	cHashMap();

	// Inserts a person at this index
	void Insert(std::string index, sPerson data);

	// Reutrns true if there is a person at this index
	bool GetPersonAt(std::string index, sPerson &data);

private:

	unsigned int m_CurrentArraySize;	// 100 default
	void m_InitArray(void);

	unsigned int m_calcHash(std::string index);

	// Here's where our data is
	// NOTE: This is an array of pointers, but since it's dynamic, 
	//       it's *also* a pointer.
	// Think of it this way:
	//   sPerson*   *m_pPeople;
	sPerson** m_pPeople;

//	cList** m_pListOfPeople;

//	sPerson myArray[100];
//	sPerson* myArray = new sPerson[100];
//
//	(sPerson*)* myArray = new (sPerson*)[100]

};

#endif
