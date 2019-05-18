#pragma once

#include "iMonster.h"
#include "iMediator_MonsterInterface.h"
#include <vector>

class cMediator :
	public iMediator_MonsterInterface		// What the monsters see
{
public:
	// Called to load monsters into the world
	void LoadMonster( iMonster* pMonster );


	// The monsters might want to call
	iMonster* findMonsterByName(std::string name);
	iMonster* findFirstMonsterByType(std::string tyoe);
	iMonster* findClosestMonster( float x, float y, float z );
	// ... and so on

	virtual void SendMessageToMonster( std::vector<std::string> vecMessage );


private:

	std::vector<iMonster*> m_vec_pMonsters;

};

