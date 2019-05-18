#include "cBST.h"

cBST::cBST()
{
	this->pRootNode = NULL;

	return;
}

cBST::cNode::cNode()
{
	this->pGreaterThan = NULL;
	this->pLessThan = NULL;
	return;
}

bool cBST::InsertPerson( std::string index, sPerson thePerson )
{
	// Is there anything there at all?	
	if ( this->pRootNode == NULL )		// 1st insert
	{
		// make a copy of the person and store
		cNode* pNewNode = new cNode();

		// Copy the passed data into this node
		pNewNode->theData = thePerson;
		pNewNode->indexValue = index;

		// Store as the 1st node
		this->pRootNode = pNewNode;
		return true;
	}
	else
	{
		// Find a location to insert this node...
		// Hold on, wait for recursion... 

		return this->m_InsertAtThisNode( index, thePerson, 
										 this->pRootNode );

	}


	return false;
}

bool cBST::m_InsertAtThisNode( std::string index, sPerson thePerson, 
							   cNode* pNodeToTest )
{
	// See if I should go down the left or right side of this node.
	// Is it "greater" or "less than" the current node value?

	if ( pNodeToTest->indexValue == index )
	{
		// The node values are the same, so overwrite
		pNodeToTest->theData = thePerson;
		pNodeToTest->indexValue = index;
		return true;
	}
	else if ( pNodeToTest->indexValue < index ) //"michael" > "robin"
	{
		// Check the "greater than" side
		// Is the node to the right NULL (i.e. nothing there, yet)
		if ( pNodeToTest->pGreaterThan == NULL )
		{
			cNode* pNewNode = new cNode();
			pNewNode->theData = thePerson;
			pNewNode->indexValue = index;
			pNodeToTest->pGreaterThan = pNewNode;
			return true;
		}
		else
		{	// There's something there, already, so call again
			return this->m_InsertAtThisNode( index, thePerson, 
									         pNodeToTest->pGreaterThan );
		}

	}
	else //( pNodeToTest->theData.last > thePerson.last )
	{	// check for the "greater than" side
		if ( pNodeToTest->pLessThan == NULL )
		{
			cNode* pNewNode = new cNode();
			pNewNode->theData = thePerson;
			pNewNode->indexValue = index;
			pNodeToTest->pLessThan = pNewNode;
			return true;
		}
		else
		{	// There's something there, already, so call again
			return this->m_InsertAtThisNode( index, thePerson, 
									         pNodeToTest->pLessThan );
		}
	}

	// All is lost, forever lost... 
	return false;
}
