#ifndef _iMonster_HG_
#define _iMonster_HG_

#include <string>
#include <vector>

// Interface class in C++ is:
// - Virtual 
// - it's a regular class
// - Shouldn't have any data (can, but this is Very Very Bad)
// - ONLY have methods (NO data, although you *CAN* technically)
// - ONLY "pure virtual" (except d'tor)


class iMonster
{
public:
	//iMonster();
	virtual ~iMonster() {};		// A bug if you don't have it

	// Here's all the methods all monsters should have
	virtual void PrintMonster(void) = 0;

	// Added to use weapons
	virtual void Attack(void) = 0;

	virtual void Move(void) = 0;

	// This is by whoever is attacking
	virtual void TakeDamage(float hitPoints) = 0;



// NO DATA!!!!



};


#endif
