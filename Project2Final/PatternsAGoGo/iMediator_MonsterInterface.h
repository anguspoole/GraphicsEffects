#pragma once

#include <string>
#include "iMonster.h"

class iMediator_MonsterInterface
{
public:
	virtual ~iMediator_MonsterInterface() {};	// empty d'tor

	// The monsters are only allows to see these methods...
	virtual iMonster* findMonsterByName(std::string name) = 0;
	//virtual iMonster* findFirstMonsterByType(std::string type) = 0;
	//virtual iMonster* findClosestMonster( float x, float y, float z ) = 0;

	virtual void SendMessageToMonster( std::vector<std::string> vecMessage ) = 0;


};
