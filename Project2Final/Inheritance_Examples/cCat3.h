#pragma once
// cCat3
#include "cAnimal3.h" 

#include <string>

class cCat3 : public cAnimal3
{
public:
	cCat3();
	virtual ~cCat3();

	// Woof() and Meow()
	virtual void MakeNoise(void);		// Cat's method

	std::string name;	// Common
	float AmountOfBoredom;


};