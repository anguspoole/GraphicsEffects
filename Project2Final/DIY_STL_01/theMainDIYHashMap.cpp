#include "DIY_Hash_Map.h"
#include "cPerson.h"
#include <iostream>


int main_DIY_HASHMAP()
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

	cHashMap myMap;

	myMap.Insert("Michael", michael);
	myMap.Insert("Robin", robin);
	myMap.Insert("Fraser", fraser);
	myMap.Insert("Jacob", jacob);

	sPerson personToGet;

	myMap.GetPersonAt("Fraser", personToGet);


	return 0;
}
