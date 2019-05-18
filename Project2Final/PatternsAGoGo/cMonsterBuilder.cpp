#include "cMonsterBuilder.h"

#include "cPistol.h"
#include "cJetPack.h"
#include "cKnife.h"

#include "iMonster.h"

#include "iInvisibleOgre_BuilderInterface.h"
#include "iNecroticMonster_BuilderInterface.h"
#include "iMonster_BuilderInterface.h"

//#include "cInvisibleOgre.h"
//#include "cMonster.h"
//#include "cNecroticMonster.h"

cMonsterBuilder::cMonsterBuilder()
{
	return;
}

void cMonsterBuilder::SetMediator( iMediator_MonsterInterface* pMediator )
{
	this->m_pTheMediator = pMediator;
	return;
}


cMonsterBuilder::~cMonsterBuilder()
{
	return;
}

void cMonsterBuilder::BuildMonster( std::string monsterType, iMonster* &pTheMonster )
{

	if ( monsterType == "RegularMonster" )
	{
		// Moved the "assmebly" or "building" of the monster
		// to here (this "builder" class)

//		((cMonster*)pTheMonster)->m_pTheKnife = new cKnife();
		iMonster_BuilderInterface* pMonster 
			= dynamic_cast<iMonster_BuilderInterface*>(pTheMonster);

		pMonster->SetKnife( new cKnife() );
		pMonster->SetSkateboard( new cSkateboard() );

		// AND set the mediator, too!
		pMonster->SetMediator(this->m_pTheMediator);

		//((iMonster_BuilderInterface*)pTheMonster)->SetKnife( new cKnife() );
		//((iMonster_BuilderInterface*)pTheMonster)->SetSkateboard( new cSkateboard() );

		//// AND set the mediator, too!
		//((iMonster_BuilderInterface*)pTheMonster)->SetMediator(this->m_pTheMediator);

	}
	else if ( monsterType == "NecroticMonster" )
	{
		//((cNecroticMonster*)pTheMonster)->m_pPistol_01 = new cPistol();
		//((cNecroticMonster*)pTheMonster)->m_pPistol_02 = new cPistol();
		//((cNecroticMonster*)pTheMonster)->m_pJetPack = new cJetPack();

		iNecroticMonster_BuilderInterface* pMonster 
			= dynamic_cast<iNecroticMonster_BuilderInterface*>(pTheMonster);

		pMonster->SetPistol( 1, new cPistol() );
		pMonster->SetPistol( 2, new cPistol() );
		pMonster->SetPistol( 3, new cPistol() );
		pMonster->SetJetPack( new cJetPack() );

		// AND set the mediator, too!
		pMonster->SetMediator(this->m_pTheMediator);

		//((iNecroticMonster_BuilderInterface*)pTheMonster)->SetPistol( 1, new cPistol() );
		//((iNecroticMonster_BuilderInterface*)pTheMonster)->SetPistol( 2, new cPistol() );
		//((iNecroticMonster_BuilderInterface*)pTheMonster)->SetPistol( 3, new cPistol() );
		//((iNecroticMonster_BuilderInterface*)pTheMonster)->SetJetPack( new cJetPack() );
		//
		//// AND set the mediator, too!
		//((iNecroticMonster_BuilderInterface*)pTheMonster)->SetMediator(this->m_pTheMediator);

	}
	else if ( monsterType == "InvisibleOgre" )
	{
//		((cInvisibleOgre*)pTheMonster)->m_pThePistol = new cPistol();

		iInvisibleOgre_BuilderInterface* pMonster 
			= dynamic_cast<iInvisibleOgre_BuilderInterface*>(pTheMonster);

		//// Can call this because it's public!
		//((iInvisibleOgre_BuilderInterface*)pTheMonster)->SetPistol( new cPistol() );
//
		//// AND set the mediator, too!
		//((iInvisibleOgre_BuilderInterface*)pTheMonster)->SetMediator(this->m_pTheMediator);

		// Can call this because it's public!
		pMonster->SetPistol( new cPistol() );

		// AND set the mediator, too!
		pMonster->SetMediator(this->m_pTheMediator);

	}


	return;
}
