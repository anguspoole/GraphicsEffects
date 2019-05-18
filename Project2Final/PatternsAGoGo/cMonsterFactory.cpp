#include "cMonsterFactory.h"

#include <iostream>

// Sorry, forgot to include this
#include "cMonsterFactory_Imp.h"

cMonsterFactory::cMonsterFactory(iMediator_MonsterInterface* pMediator)
{
	std::cout << "cMonsterFactory()" << std::endl;

	this->m_pImp = new cMonsterFactory_Imp();
	this->m_pImp->SetMediator(pMediator);

	return;
}


cMonsterFactory::~cMonsterFactory()
{
	std::cout << "~cMonsterFactory()" << std::endl;

	delete this->m_pImp;

	return;
}

bool cMonsterFactory::isMonsterTypeValid( std::string MonsterType )
{
	return true;
}

// Return a common "base" monster
// Has to take a native or known type
iMonster* cMonsterFactory::CreateMonster( std::string MonsterType )
{
	// Call the imp indirectly

	return this->m_pImp->CreateMonster( MonsterType );
}
