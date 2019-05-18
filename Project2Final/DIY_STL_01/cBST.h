#ifndef _cBST_HG_
#define _cBST_HG_

#include "cPerson.h"
#include <string>

// "BST" stands for "Binary Search Tree"

class cBST
{
public:
	cBST();

	class cNode
	{
	public:
		cNode();
		cNode* pLessThan;
		cNode* pGreaterThan;
		std::string indexValue;
		sPerson theData;
	};

	cNode* pRootNode;
	
	bool InsertPerson( std::string index, sPerson thePerson );
	bool DeletePerson( std::string index );
	bool FindPerson( std::string index, sPerson &thePerson );

private:
	// Check this node, and see if we can insert here
	bool m_InsertAtThisNode( std::string index, sPerson thePerson, 
							 cNode* pNodeToTest );
};

#endif
