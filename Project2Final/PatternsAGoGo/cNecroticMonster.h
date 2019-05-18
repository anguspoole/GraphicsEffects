#ifndef _cNecroticMonster_HG_
#define _cNecroticMonster_HG_

#include "iMonster.h"		// include interface class

#include <string>

// Assume that it's all polymorphic (virtual)

#include "cPistol.h"
#include "cJetPack.h"
#include "iNecroticMonster_BuilderInterface.h"

class cNecroticMonster : 
	public iMonster,
	public iNecroticMonster_BuilderInterface
{
public:
	cNecroticMonster();
	virtual ~cNecroticMonster();		// A bug if you don't have it

	virtual void PrintMonster(void);

	virtual void Attack(void);

	virtual void Move(void);

	virtual void TakeDamage(float hitPoints);

	// Just with the monster
	void ShrivelUp(float seconds);
	void VomitAndDie(void);



	void FlyAwayWithJetPack(void);

	std::string name;
	std::string colour;
	float health;		

	// This is here so THE BUILDER can create and set the pistol
	// is now part of necrotic interface for builder
	virtual void SetPistol(int pistolNum, cPistol* pThePistol);
	virtual void SetJetPack( cJetPack* pTheJetPack );
	virtual void SetMediator(iMediator_MonsterInterface* pMediator);


private:
	cPistol* m_pPistol[3];
	cJetPack* m_pJetPack;

	iMediator_MonsterInterface* m_pMediator;
};


#endif
