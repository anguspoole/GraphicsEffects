#ifndef _cList_HG_
#define _cList_HG_

#include "cPerson.h"

class cList
{
public:
	cList();
	~cList();

	class cNode
	{
	public:
		cNode();
		~cNode() {};
		sPerson theData;		// Note "stack based" person data
		cNode* pNextNode;		// Singly linked list
		cNode* pPriorNode;		// Doubly linked list
	};


	//void InsertAt(int location, sPerson);

	void InsertAtCurrentLocation(sPerson);

	// This will delete the object and update pointers
	void DeleteAtCurrentLocation(void);

	void MoveToStart(void);
	// Returns true if this worked
	bool MoveToNext(void);

	sPerson GetPersonAtCurrent(void);

	unsigned int getSize(void);
//	void MoveToPrevious(void);

private:

	// This is the "head" or "root" of the list
	cNode* m_pRootNode;		// NULL
	cNode* m_pCurrentNode;	// NULL
};

#endif
