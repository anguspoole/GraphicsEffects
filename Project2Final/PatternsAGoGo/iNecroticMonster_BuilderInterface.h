#ifndef _iNecroticMonster_BuilderInterface_HG_
#define _iNecroticMonster_BuilderInterface_HG_

#include "cPistol.h"
#include "cJetPack.h"
#include "iMonster_BuilderInterface.h"

class iNecroticMonster_BuilderInterface
{
public:
	virtual ~iNecroticMonster_BuilderInterface() {};

		// This is here so THE BUILDER can create and set the pistol
	virtual void SetPistol(int pistolNum, cPistol* pThePistol) = 0;
	virtual void SetJetPack( cJetPack* pTheJetPack ) = 0;

	virtual void SetMediator(iMediator_MonsterInterface* pMediator) = 0;


};

#endif
