#include "cList.h"

cList::cList()
{
	this->m_pCurrentNode = NULL;
	this->m_pRootNode = NULL;

	return;
}

cList::~cList()
{
	//TODO: Clean up

	return;
}

cList::cNode::cNode()
{
	this->pNextNode = NULL;
	this->pPriorNode = NULL;
	return;
}

void cList::InsertAtCurrentLocation(sPerson newPerson)
{
	// Is the current node NULL?
	if ( this->m_pCurrentNode == NULL )
	{
		cNode* pNewNode = new cNode();
		// Copy the data to this node
		pNewNode->theData = newPerson;

		// Point the current node to this node
		this->m_pCurrentNode = pNewNode;

		// Is this the very first node, too?
		if ( this->m_pRootNode == NULL )
		{	
			// Yes, so point to this as well
			this->m_pRootNode = pNewNode;
		}
	}
	else
	{	// There's already something at the "current" node

		cNode* pNewNode = new cNode();
		// Copy the information
		pNewNode->theData = newPerson;

		// Place this node AFTER the current node
		// By taking the current node's "next node" 
		//  and pointing it to this new node.

		this->m_pCurrentNode->pNextNode = pNewNode;

		// Doubly linked list.. points to prior node
		pNewNode->pPriorNode = this->m_pCurrentNode;

		// Move the current node pointer
		this->m_pCurrentNode = pNewNode;
	}



	return;
}


void cList::MoveToStart(void)
{
	// point the current node to the root
	this->m_pCurrentNode = this->m_pRootNode;
	return;
}

bool cList::MoveToNext(void)
{
	// See if the current node has a "next node"
	if ( this->m_pCurrentNode->pNextNode != NULL )
	{
		// It's not NULL, so must be pointing to something
		this->m_pCurrentNode = this->m_pCurrentNode->pNextNode;

		return true;
	}
	return false;
}

sPerson cList::GetPersonAtCurrent(void)
{
	return this->m_pCurrentNode->theData;
}

void cList::DeleteAtCurrentLocation(void)
{
	// Need to point the "prior" node to the "next" node

	//   CURRENT NODE's prior node
	//        ^           ^
	//        |           |
	//   CURRENT NODE     |
	//        |           |
	//        v           v
	//   CURRENT NODE's next node

	// Points the next to the prior
	this->m_pCurrentNode->pNextNode->pPriorNode = 
		this->m_pCurrentNode->pPriorNode;

	// Point the prior to the next
	this->m_pCurrentNode->pPriorNode->pNextNode =
		this->m_pCurrentNode->pNextNode;

	cNode* pNewCurrent = this->m_pCurrentNode->pPriorNode;

	// Delete the current
	delete this->m_pCurrentNode;

	// Update new current

	this->m_pCurrentNode = pNewCurrent;

}
