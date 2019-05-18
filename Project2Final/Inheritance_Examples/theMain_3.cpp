// 
#include <vector>
#include "cAnimal3.h"
#include "cDog3.h"
#include "cCat3.h"
#include "cSuperDog.h"


int main()
{
	std::vector<cAnimal3*> vec_pAnimals;
	//std::vector<cDog3*> vec_pDogs;
	//std::vector<cCat3*> vec_pCats;

	cDog3* pDog = new cDog3();
	cCat3* pCat = new cCat3();
	cSuperDog* pSDog = new cSuperDog();


//	cAnimal3* pDog = new cDog3();
//	cAnimal3* pCat = new cCat3();

	vec_pAnimals.push_back( pDog );
//	vec_pAnimals.push_back( pCat );

	vec_pAnimals[0]->MakeNoise();		// Dog
//	vec_pAnimals[1]->MakeNoise();		// Cat

	delete pDog;

	//cDog3* pTheDog = (cDog3*)vec_pAnimals[0];
	//cCat3* ptheCat = (cCat3*)vec_pAnimals[1];

	//pTheDog->MakeNoise();
	//ptheCat->MakeNoise();

	//for ( int x; x!= vec_pAnimals.size() x++ )
	//{
	//	vec_pAnimals[x]->MakeNoise();
	//}


	return 0;
}