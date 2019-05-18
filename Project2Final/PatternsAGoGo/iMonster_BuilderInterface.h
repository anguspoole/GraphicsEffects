#ifndef _iMonster_BuilderInterface_HG_
#define _iMonster_BuilderInterface_HG_

#include "cKnife.h"
#include "cSkateboard.h"
#include "iMediator_MonsterInterface.h"

class iMonster_BuilderInterface
{
public:
	virtual ~iMonster_BuilderInterface() {};

		// This is here so THE BUILDER can create and set the pistol
	virtual void SetKnife(cKnife* pTheKnife) = 0;
	virtual void SetSkateboard(cSkateboard* pTheSkateBoard) = 0;
	virtual void SetMediator(iMediator_MonsterInterface* pMediator) = 0;


};

#endif
