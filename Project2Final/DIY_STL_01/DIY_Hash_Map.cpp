#include "DIY_Hash_Map.h"

cHashMap::cHashMap()
{
	// Default size is 100 just because...
	this->m_CurrentArraySize = 100;
	
	this->m_InitArray();

	return;
}

void cHashMap::m_InitArray()
{
//	sPerson* m_pPeople;

	// Note that this is an array of POINTERS, so note the 
	//  slightly odd syntax
	// sPerson** m_pPeople;
	// (sPerson*)* m_pPeople;

	this->m_pPeople = new sPerson*[this->m_CurrentArraySize];


	// Clear array to zero
	for ( int index = 0; index != this->m_CurrentArraySize; index++ )
	{
		// Set all these pointers to NULL (0)
		this->m_pPeople[index] = NULL;
	}

	return;
}

unsigned int cHashMap::m_calcHash(std::string indexString)
{
	// Create a "hash value" to determine where, in the array
	//  of items we want to put this unique value....

	// Add up all letters in the name, then get mod of how
	//  bit my array is...

	unsigned int indexHashValue = 0;

	for ( unsigned int charIndex = 0; 
		  charIndex != indexString.size(); charIndex++ )
	{
		char curChar = indexString[charIndex];

		indexHashValue += (unsigned int)curChar;
	}

	indexHashValue = indexHashValue % this->m_CurrentArraySize;

	return indexHashValue;
}

void cHashMap::Insert(std::string index, sPerson data)
{
	unsigned int indexHash = this->m_calcHash(index);  

	// Create a copy of this thing to place in the array of information:
	sPerson* pNewPerson = new sPerson;

	// Copy the information
	(*pNewPerson) = data;

	this->m_pPeople[indexHash] = pNewPerson; 

	return;
}


// Reutrns true if there is a person at this index
bool cHashMap::GetPersonAt(std::string index, sPerson &data)
{
	//DOTO: This code
	unsigned int indexHash = this->m_calcHash(index);

	if ( this->m_pPeople == NULL )
	{
		// there's nothing there
		return false;
	}

	data = *(this->m_pPeople[indexHash]);

	return true;
}
