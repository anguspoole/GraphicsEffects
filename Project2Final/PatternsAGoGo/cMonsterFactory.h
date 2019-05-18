#ifndef _cMonsterFactory_HG_
#define _cMonsterFactory_HG_

#include <string>
#include "iMonster.h"


//#include "cMonsterFactory_Imp.h"
// forward declaration
class cMonsterFactory_Imp;

#include "iMediator_MonsterInterface.h"

class cMonsterFactory
{
public:
	cMonsterFactory(iMediator_MonsterInterface* pMediator);
	~cMonsterFactory();

	bool isMonsterTypeValid( std::string MonsterType );
	// Return a common "base" monster
	// Has to take a native or known type
	iMonster* CreateMonster( std::string MonsterType );
	
private:
	cMonsterFactory();

	cMonsterFactory_Imp* m_pImp;

	iMediator_MonsterInterface* m_pMediator;
};

#endif
