#ifndef _iInvisibleOgre_BuilderInterface_HG_
#define _iInvisibleOgre_BuilderInterface_HG_

// This is an INTERFACE class
// Pure virtual methods
// No data.
// Virtual destructor

#include "cPistol.h"
#include "iMediator_MonsterInterface.h"

class iInvisibleOgre_BuilderInterface
{
public:
	virtual ~iInvisibleOgre_BuilderInterface() {};	// Does nothing

	// This is here so **ONLY** THE BUILDER can create and set the pistol
	virtual void SetPistol(cPistol* pThePistol) = 0;

	virtual void SetMediator(iMediator_MonsterInterface* pMediator) = 0;


};

#endif