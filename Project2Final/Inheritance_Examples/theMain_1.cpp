// theMain.cpp
#include <vector>
#include <iostream>
#include "cCat1.h"
#include "cDog1.h"


int main_version_1()
{
	cCat1 a;		a.Meow();
	cDog1 b;		b.Woof();

	std::vector<cCat1> vecCats;
	std::vector<cDog1> vecDogs;
//	vecCats.push_back( b );	// Makes sense

	std::cout << "Here we go!" << std::endl;

	std::vector<void*> vecAll;
	cCat1* pTheCat = new cCat1();
	pTheCat->name = "Ginger";

	cDog1* pTheDog = new cDog1();
	pTheDog->colour = "Brown";

	vecAll.push_back(pTheDog);		// [0]
	vecAll.push_back(pTheCat);		// [1]

	cCat1* pACat = (cCat1*)vecAll[0];  // DOG!!!!
	pACat->Meow();

	cDog1* pADog = (cDog1*)vecAll[1];	 // CAT WHAT THE WHAT???!?
	pADog->Woof();


	//( (cCat*)vecAll[0] )->Meow();
	//( (cDog*)vecAll[1] )->Woof();


	return 0;
}
