#include "cInvisibleOgre.h"
#include <iostream>

const std::string UNNAMED_MONSTER = "UNKNOWN";
const std::string UNKNOWN_COLOUR = "UNKNOWN_COLOURS";

cInvisibleOgre::cInvisibleOgre()
{
	this->name = UNNAMED_MONSTER;
	this->colour = UNKNOWN_COLOUR;
	this->health = 110.0f;

	std::cout << "cInvisibleOgre() is created" << std::endl;

	this->m_pMediator = NULL;

	// This is likely VERY complicated.
	// And we'll need to know a LOT about the knife to create it
//	this->m_pThePistol = new cPistol();

	return;
}


cInvisibleOgre::~cInvisibleOgre()
{
	std::cout << "cNecroticMonster() is destroyed" << std::endl;
	return;
}

void cInvisibleOgre::PrintMonster(void)
{
	std::cout 
		<< "cInvisibleOgre: "
		<< this->name << " has " 
		<< this->colour << " fur" << std::endl;

	return;
}


void cInvisibleOgre::Attack(void)
{
	std::cout << "cInvisibleOgre::Attack(): " << std::endl;

	this->m_pThePistol->Shoot();

	return;
}

void cInvisibleOgre::Move(void)
{
	std::cout << "cInvisibleOgre::Move(): " << std::endl;


	return;
}


void cInvisibleOgre::TakeDamage(float hitPoints)
{
	// TODO:
	std::cout << "cInvisibleOgre::TakeDamage()" << std::endl;

	return;
}



// *****
	// This is here so THE BUILDER can create and set the pistol
// Part of the iInvisibleOgre_BuilderInterface interface
void cInvisibleOgre::SetPistol(cPistol* pThePistol)
{
	this->m_pThePistol = pThePistol;
	return;
}
 void cInvisibleOgre::SetMediator(iMediator_MonsterInterface* pMediator)
 {
	this->m_pMediator = pMediator;
	return;
 }
