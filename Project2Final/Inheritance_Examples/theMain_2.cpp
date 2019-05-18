// 
#include <vector>
#include "cAnimal.h"
#include "cDog2.h"
#include "cCat2.h"


int main_version_2()
{
	std::vector<cAnimal*> vec_pAnimals;

	cDog2* pDog = new cDog2();
	cCat2* pCat = new cCat2();

	vec_pAnimals.push_back( pDog );
	vec_pAnimals.push_back( pCat );

//	vec_pAnimals[0]->MakeNoise();		// Dog
//	vec_pAnimals[1]->MakeNoise();		// Cat

	cDog2* pTheDog = (cDog2*)vec_pAnimals[0];
	cCat2* ptheCat = (cCat2*)vec_pAnimals[1];

	pTheDog->MakeNoise();
	ptheCat->MakeNoise();

	//for ( int x; x!= vec_pAnimals.size() x++ )
	//{
	//	vec_pAnimals[x]->MakeNoise();
	//}


	return 0;
}