#include "cNecroticMonster.h"
#include <iostream>

const std::string UNNAMED_MONSTER = "UNKNOWN";
const std::string UNKNOWN_COLOUR = "UNKNOWN_COLOURS";

cNecroticMonster::cNecroticMonster()
{
	this->name = UNNAMED_MONSTER;
	this->colour = UNKNOWN_COLOUR;
	this->health = 100.0f;

	this->m_pMediator = NULL;

	// This is likely VERY complicated.
	// And we'll need to know a LOT about the knife to create it
//	this->m_pPistol_01 = new cPistol();
//	this->m_pPistol_02 = new cPistol();

//	this->m_pJetPack = new cJetPack();

	std::cout << "cNecroticMonster() is created" << std::endl;
	return;
}

cNecroticMonster::~cNecroticMonster()
{
	std::cout << "cNecroticMonster() is destroyed" << std::endl;
	return;
}

void cNecroticMonster::PrintMonster(void)
{
	std::cout 
		<< "cNecroticMonster: "
		<< this->name << " has " 
		<< this->colour << " fur" << std::endl;

	return;
}

void cNecroticMonster::Attack(void)
{
	std::cout << "cNecroticMonster::Attack(): " << std::endl;
	this->m_pPistol[0]->Shoot();
	this->m_pPistol[1]->Shoot();
	this->m_pPistol[2]->Shoot();

	// Fred takes a hit!
	iMonster* pMonsterImAttacking = this->m_pMediator->findMonsterByName("Fred");
	pMonsterImAttacking->TakeDamage( 50.0f );

	std::vector<std::string> vecAttackFred;
	vecAttackFred.push_back("Attack");
	vecAttackFred.push_back("Fred");
	vecAttackFred.push_back("50.0");

	this->m_pMediator->SendMessageToMonster(vecAttackFred);

	std::vector<std::string> vecKillAllOgresWithVenomUpTo150m;
	vecKillAllOgresWithVenomUpTo150m.push_back("AreaAttack");
	vecKillAllOgresWithVenomUpTo150m.push_back("PlasmaVenom");
	vecKillAllOgresWithVenomUpTo150m.push_back("OrgesOnly");
	vecKillAllOgresWithVenomUpTo150m.push_back("150.0");
	this->m_pMediator->SendMessageToMonster(vecKillAllOgresWithVenomUpTo150m);
	return;
}

void cNecroticMonster::Move(void)
{
	std::cout << "cNecroticMonster::Move(): " << std::endl;
	
	this->FlyAwayWithJetPack();

	return;
}


void cNecroticMonster::TakeDamage(float hitPoints)
{
	// TODO:
	std::cout << "cNecroticMonster::TakeDamage()" << std::endl;
	return;
}

//
//void cNecroticMonster::FlyAwayWithJetPack(void)
//{
//	this->m_pJetPack->FlyAway();
//	return;
//}


	// This is here so THE BUILDER can create and set the pistol
void cNecroticMonster::SetPistol(int pistolNum, cPistol* pThePistol)
{
	if ( pistolNum >= 1  && pistolNum <= 3 )
	{
		this->m_pPistol[pistolNum - 1] = pThePistol;
	}
	return;
}

	
void cNecroticMonster::SetJetPack( cJetPack* pTheJetPack )
{
	this->m_pJetPack = pTheJetPack;
	return;
}

 void cNecroticMonster::SetMediator(iMediator_MonsterInterface* pMediator)
 {
	this->m_pMediator = pMediator;
	return;
 }
