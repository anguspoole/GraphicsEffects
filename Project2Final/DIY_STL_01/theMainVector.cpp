#include "cVector.h"

#include "cPerson.h"
#include <iostream>

int main_vector()
{
	cVector myVec;

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

	myVec.InsertPersonAtEnd( michael );
	myVec.InsertPersonAtEnd( robin );
	myVec.InsertPersonAtEnd( fraser );
	myVec.InsertPersonAtEnd( jacob );

	for ( unsigned int index = 0; index != myVec.GetSize(); index++ )
	{
		sPerson thePerson;
		myVec.GetPersonAtIndex( index, thePerson );

		std::cout << index << " "
			<< thePerson.first << " " 
			<< thePerson.last << std::endl;
	}


	return 0;
}
