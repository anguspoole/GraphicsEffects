#include <map>
#include "cPerson.h"
#include <iostream>
#include <string>

int main_STL_MAP()
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

	std::map<std::string /*first*/, sPerson> myMap;
	myMap[michael.first] = michael;
	myMap[robin.first] = robin;
	myMap[fraser.first] = fraser;
	myMap[jacob.first] = jacob;


	sPerson thePerson = myMap["Jacob"];

	return 0;
}
