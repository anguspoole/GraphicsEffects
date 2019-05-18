#ifndef _cMonsterBuilder_HG_
#define _cMonsterBuilder_HG_

// Only include interface.
// DON'T include ANYTHING that's details
// Pass a "general" (usually native) type, NOT an enum

// forward declare to NOT know too much about the monster.
// Needed because we have to pass monsters between the factory
//	and the builder classes
class iMonster;
//#include "iMonster.h"

#include <string>
#include "iMediator_MonsterInterface.h"

class cMonsterBuilder
{
//cMonsterBuilder
public:
	cMonsterBuilder();
	~cMonsterBuilder();
	// The factory will make monster, and pass this into here
	//	to have stuff added to it. The "monsterType" determines what
	//	kind of stuff to add (build, assemble, etc.)
	void BuildMonster( std::string monsterType, iMonster* &pTheMonster );

	void SetMediator( iMediator_MonsterInterface* pMediator );


private:
	
	iMediator_MonsterInterface* m_pTheMediator;
};


#endif 

