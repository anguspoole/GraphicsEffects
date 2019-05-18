#include "cBST.h"
#include <iostream>


int main_BST()
{
	sPerson michael;
	michael.first = "Michael";
	michael.last = "Feeney";
	sPerson robin;
	robin.first = "Robin";
	robin.last = "Bobbin";
	sPerson fraser;
	fraser.first = "Fraser";
	fraser.last = "Fareast";
	sPerson jacob;
	jacob.first = "Jacob";
	jacob.last = "Sir";


	cBST myBST;

	myBST.InsertPerson( "Michael", michael );
	myBST.InsertPerson( "Robin", robin );
	myBST.InsertPerson( "Fraser", fraser );
	myBST.InsertPerson( "Jacob", jacob );



	return 0;
}

