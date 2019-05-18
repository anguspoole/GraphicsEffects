#include "cMediator.h"

void cMediator::LoadMonster( iMonster* pMonster )
{
	this->m_vec_pMonsters.push_back( pMonster );
	

	return;
}

iMonster* cMediator::findMonsterByName(std::string name)
{
	// For now, just return the 1st monster...
	return this->m_vec_pMonsters[0];

	//for ( std::vector<iMonster*>::iterator itMon = this->m_vec_pMonsters.begin();
	//	  itMon != this->m_vec_pMonsters.end(); itMon++ )
	//{
	//	// This the one?
	//	


	//}

	// Didn't fine one
	return NULL;
}

// Very complicated logic here, maybe?
void cMediator::SendMessageToMonster( std::vector<std::string> vecMessage )
{
	if ( vecMessage[0] == "Attack" )
	{
		iMonster* pToAttack = this->findMonsterByName( vecMessage[1] );

		pToAttack->TakeDamage( (float)atof(vecMessage[2].c_str()) );

	}
	else if ( vecMessage[0] == "LayEggs" )
	{

	}
	else if ( vecMessage[0] == "AreaAttack" )
	{
		//
	}


	return;
}
