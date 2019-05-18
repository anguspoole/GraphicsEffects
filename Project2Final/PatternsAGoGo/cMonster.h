#ifndef _cMonster_HG_
#define _cMonster_HG_

#include "iMonster.h"		// include interface class

#include <string>
#include <vector>

#include "cKnife.h"
#include "cSkateboard.h"

#include "iMonster_BuilderInterface.h"

// To get at the mediator
// NOTE: It's NOT the "real" mediator, just the specific interface
#include "iMediator_MonsterInterface.h"

//class cMonsterBuilder;

// Assume that it's all polymorphic (virtual)
class cMonster : 
	public iMonster, 
	public iMonster_BuilderInterface
{
public:

// DON'T DO THIS (unless it's dire situation)
//	friend cMonsterBuilder;

	cMonster();
	virtual ~cMonster();		// A bug if you don't have it

	virtual void PrintMonster(void);

	virtual void Attack(void);

	virtual void Move(void);

	virtual void TakeDamage(float hitPoints);

	// Just with the monster
	void DieHorribleDeath(std::string sound);


	void DoSomething(void);

	std::string name;
	std::string colour;
	float health;		 

	//// Sally has to:
	//// - Have this loaded with data (and updated)
	//// - Know abuot the monsters
	//// - Find a monster...
	//std::vector< iMonster* > vec_pTheOtherMonsters;

	// This is here so THE BUILDER can create and set the pistol
	// iMonster_BuilderInterface
	virtual void SetKnife(cKnife* pTheKnife);
	virtual void SetSkateboard(cSkateboard* pTheSkateBoard) ;
	virtual void SetMediator(iMediator_MonsterInterface* pMediator);

private:
	iMediator_MonsterInterface* m_pMediator;

	int shoeSize;
	bool LikesChocolate;

	cKnife* m_pTheKnife;
	cSkateboard* m_pTheSkateboard;
};


#endif
