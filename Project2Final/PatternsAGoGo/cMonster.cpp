#include "cMonster.h"
#include <iostream>

const std::string UNNAMED_MONSTER = "UNKNOWN";
const std::string UNKNOWN_COLOUR = "UNKNOWN_COLOURS";

cMonster::cMonster()
{
	this->name = UNNAMED_MONSTER;
	this->colour = UNKNOWN_COLOUR;
	this->health = 100.0f;


	this->m_pMediator = NULL;

	// This is likely VERY complicated.
	// And we'll need to know a LOT about the knife to create it
//	this->m_pTheKnife = new cKnife();
	// Setting the mesh
	// Setting the sound, colour, whatever
	// I need to know a lot about the inner workings of everything
	//	- Means you change ANYTHING (like the VAOMeshManager...)

	std::cout << "cMonster() is created" << std::endl;
	return;
}

cMonster::~cMonster()
{
	std::cout << "cMonster() is destroyed" << std::endl;
	return;
}

void cMonster::PrintMonster(void)
{
	std::cout 
		<< "cMonster:" 
		<< this->name << " has " 
		<< this->colour << " fur" << std::endl;

	return;
}

void cMonster::DoSomething(void)
{

	return;
}

//// This is THE SAME for EVERY monster
//void cMonster::KillARandomMonster(void)
//{
//	// iMonster
//	std::cout << "cMonster::KillARandomMonster" << std::endl;
//	return;
//}

void cMonster::Attack(void)
{
	std::cout << "cMonster::Attack(): " << std::endl;

	this->m_pTheKnife->StabbyStab();

	return;
}

void cMonster::Move(void)
{
	std::cout << "cMonster::Move(): " << std::endl;

	this->m_pTheSkateboard->GrindOnStairs( 50.0f );

	return;
}

void cMonster::TakeDamage(float hitPoints)
{
	// TODO:
	std::cout << "cMonster::TakeDamage()" << std::endl;

	return;
}



// This is here so THE BUILDER can create and set the pistol
void cMonster::SetKnife(cKnife* pTheKnife)
{
	this->m_pTheKnife = pTheKnife;
	return;
}

void cMonster::SetSkateboard(cSkateboard* pTheSkateBoard)
{
	this->m_pTheSkateboard = pTheSkateBoard;
	return;
}

 void cMonster::SetMediator(iMediator_MonsterInterface* pMediator)
 {
	this->m_pMediator = pMediator;
	return;
 }
