#include <list>
#include "cPerson.h"
#include <iostream>
#include <iterator>

int main_STL_LIST()
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

	std::list<sPerson> myList;

	myList.insert( myList.begin(), michael );
	myList.insert( myList.begin(), robin );
	myList.insert( myList.begin(), fraser );
	myList.insert( myList.begin(), jacob );

	std::list<sPerson>::iterator itPer; 

	itPer = myList.begin();
	itPer++;
	itPer++;

	std::cout << itPer->first << std::endl;

	// Can you even do this?? 
	myList.insert( myList.end(), michael );
	myList.insert( myList.end(), robin );
	myList.insert( myList.end(), fraser );
	myList.insert( myList.end(), jacob );

	return 0;
}
