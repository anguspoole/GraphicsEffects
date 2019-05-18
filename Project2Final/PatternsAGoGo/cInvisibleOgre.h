#ifndef _cInvisibleOgre_HG_
#define _cInvisibleOgre_HG_

#include "iMonster.h"		// include interface class

#include <string>

#include "cPistol.h"

#include "iInvisibleOgre_BuilderInterface.h"

// Assume that it's all polymorphic (virtual)
class cInvisibleOgre : 
	public iMonster,				// public iMonster
	public iInvisibleOgre_BuilderInterface
{
public:
	cInvisibleOgre();
	virtual ~cInvisibleOgre();		// A bug if you don't have it

	virtual void PrintMonster(void);

	virtual void Attack(void);

	virtual void Move(void);

	virtual void TakeDamage(float hitPoints);


	std::string name;
	std::string colour;
	float health;		 

	//// This is here so THE BUILDER can create and set the pistol\
	// Is part of iInvisibleOgre_BuilderInterface() interface
	virtual void SetPistol(cPistol* pThePistol);
	virtual void SetMediator(iMediator_MonsterInterface* pMediator);

private:

	cPistol* m_pThePistol;

	iMediator_MonsterInterface* m_pMediator;

};


#endif
