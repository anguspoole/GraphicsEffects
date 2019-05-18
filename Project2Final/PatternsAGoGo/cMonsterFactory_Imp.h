#ifndef _cMonsterFactory_Imp_HG_
#define _cMonsterFactory_Imp_HG_

// Use a factory class or function if:
// - You have to add new types that are inherited from a base type
// - There's only ONE base type (generally)
// - Pass a 'native' or known type for creation
//   (DON'T use an enum or something like that)
// - Use an "interface class" (pure virtual class) as the "BASE" class
//   (That's what's returned)
// ONLY add the new types (.H files) In the CPP of the factory
// NEVER in the header file

#include "iMonster.h"		// Include ONLY the interface

///#include "cNecroticMonster.h"		NO!!!!!

#include <string>

#include "iMediator_MonsterInterface.h"

// Forward declare the builder
class cMonsterBuilder;

// This is to CREATE monsters
class cMonsterFactory_Imp
{
public:
	cMonsterFactory_Imp() ;
	~cMonsterFactory_Imp();

	bool isMonsterTypeValid( std::string MonsterType );
	// Return a common "base" monster
	// Has to take a native or known type
	iMonster* CreateMonster( std::string MonsterType );

	void SetMediator( iMediator_MonsterInterface* pMediator );


private:
	int Hello;
	int totalMonstersCreated;
	int ShoeSize;

	cMonsterBuilder* m_pTheMonsterBuilder;
	iMediator_MonsterInterface* m_pMediator;

};

#endif 
