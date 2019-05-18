
// Monsters attacking other monsters.
// - What's the dif bet the monsters? 
//   ("built in" or 'external')
// - Monster does or doesn't have wings?
// - Monster has Ray Gun vs Rockets
// How do the monsters communicate? 
// How do they "know" about each other? 

//#include "cMonster.h"
//#include "cNecroticMonster.h"
//#include "cInvisibleOgre.h"

#include <vector>
#include <iostream>

#include "cMonsterFactory.h"		// Only iMonster
//#include "cMonsterBuilder.h"		// Only iMonster

#include "cWorld.h"

#include "cMediator.h"

void DoGameLoop(std::vector< iMonster* > &vec_pMonsters)
{
	for ( std::vector< iMonster* >::iterator itMon = vec_pMonsters.begin();
		  itMon != vec_pMonsters.end(); itMon++ )
	{
		iMonster* pTheMonster = *itMon;
		std::cout << std::endl;
//		pTheMonster->PrintMonster();

//		pTheMonster->Attack();
		pTheMonster->Move();

		std::cout << std::endl;
	}

	return;
}

void AnotherWorld()
{
	cWorld* pWorld = cWorld::GetTheWorld();
	return;
}


int main()
{
	cWorld* pWorld = cWorld::GetTheWorld();

	cWorld::GetTheWorld()->DoThat();
	cWorld::GetTheWorld()->DoThis();

	AnotherWorld();

//	cMonster bob;
//	iMonster* pBob = new iMonster();
//	pBob->name = "Bob";

	cMediator* pTheMediator = new cMediator();

//	cMonsterFactory* pFactory = new cMonsterFactory(); 
	cMonsterFactory* pFactory = new cMonsterFactory(pTheMediator); 

	iMonster* pFred = pFactory->CreateMonster("Ogre");
	pTheMediator->LoadMonster(pFred);

	iMonster* pBob = pFactory->CreateMonster("Regular");
	pTheMediator->LoadMonster(pBob);

	iMonster* pSally = pFactory->CreateMonster("Necrotic");
	pTheMediator->LoadMonster(pSally);

	pSally->Attack();
	 
	// Sally attacks Fred
	//pSally->Attack(??);
	//pFred->TakeDamage(50.0f);

	//cMonsterBuilder* pBuilder = new cMonsterBuilder(); 
	//
	//iMonster* pBob = pBuilder->BuildMonster("RegularMonster");
	//iMonster* pSally = pBuilder->BuildMonster("NecroticMonster");
	//iMonster* pFred = pBuilder->BuildMonster("InvisibleOgre");

	

	std::vector< iMonster* > vec_pMonsters;

	vec_pMonsters.push_back(pBob);
	vec_pMonsters.push_back(pSally);
	
	if (pFred)
	{
		vec_pMonsters.push_back(pFred);
	}



	// 
	DoGameLoop( vec_pMonsters );



	//delete pBob;
	//delete pSally;

	return 0;
}
