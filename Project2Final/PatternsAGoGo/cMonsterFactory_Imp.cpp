#include "cMonsterFactory_Imp.h"

// HERE, in the CPP file is where the specific monsters
// are included *NOT* in the factory header file
#include "cMonster.h"
#include "cNecroticMonster.h"
#include "cInvisibleOgre.h"

// To add or assemble or "build" the details of the monters
// ...that are BEYOND just the base class
#include "cMonsterBuilder.h"

#include <iostream>

	// Return a common "base" monster
	// Has to take a native or known type
iMonster* cMonsterFactory_Imp::CreateMonster( std::string MonsterType )
{
	iMonster* pNM = NULL;

	if ( MonsterType == "Regular" )
	{
		pNM = new cMonster();		//*** REASON FOR ABSTRACT FACTORY***

		((cMonster*)pNM)->name = "Bob";

		// Use the builder to add the other "stuff" onto this monster
		this->m_pTheMonsterBuilder->BuildMonster( "RegularMonster", pNM );

		this->totalMonstersCreated++;
	}
	else if ( MonsterType == "Necrotic" )
	{
		pNM = new cNecroticMonster();

		((cNecroticMonster*)pNM)->name = "Sally";

		// Use the builder to add the other "stuff" onto this monster
		this->m_pTheMonsterBuilder->BuildMonster( "NecroticMonster", pNM );

		this->totalMonstersCreated++;
	}
	else if ( MonsterType == "Ogre" )
	{
		pNM = new cInvisibleOgre();

		((cInvisibleOgre*)pNM)->name = "Fred";

		// Use the builder to add the other "stuff" onto this monster
		this->m_pTheMonsterBuilder->BuildMonster( "InvisibleOgre", pNM );

		this->totalMonstersCreated++;
	}

	return pNM;
}



cMonsterFactory_Imp::cMonsterFactory_Imp()
{
	std::cout << "cMonsterFactory_Imp" << std::endl;

	this->m_pTheMonsterBuilder = new cMonsterBuilder();

	return;
}

cMonsterFactory_Imp::~cMonsterFactory_Imp()
{

	delete this->m_pTheMonsterBuilder;
	return;
}

void cMonsterFactory_Imp::SetMediator( iMediator_MonsterInterface* pMediator )
{
	this->m_pMediator = pMediator;
	this->m_pTheMonsterBuilder->SetMediator(pMediator);
	return;
}
