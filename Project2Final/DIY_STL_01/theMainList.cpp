#include "cList.h"

#include "cPerson.h"
#include <iostream>

int main_LIST()
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

	cList myList;

//	myList.MoveToStart();
	myList.InsertAtCurrentLocation( michael );
	myList.InsertAtCurrentLocation( robin );
	myList.InsertAtCurrentLocation( fraser );
	myList.InsertAtCurrentLocation( jacob );

	//myList.MoveToStart();
	//for ( int count = 0; count < 4; count++ )
	//{
	//	sPerson curPer = myList.GetPersonAtCurrent();

	//	std::cout << curPer.first << std::endl;

	//	myList.MoveToNext();
	//}

	myList.MoveToStart();
	do
	{
		sPerson curPer = myList.GetPersonAtCurrent();

		std::cout << curPer.first << std::endl;

	} while (myList.MoveToNext());

	myList.MoveToStart();
	myList.MoveToNext();
	myList.DeleteAtCurrentLocation();

	// Michael
	// Robin
	// Fraser
	// Jacob
	std::cout << "----" << std::endl;
	myList.MoveToStart();
	do
	{
		sPerson curPer = myList.GetPersonAtCurrent();

		std::cout << curPer.first << std::endl;

	} while (myList.MoveToNext());



		

	return 0;
}