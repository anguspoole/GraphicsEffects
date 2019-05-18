#pragma once
// cCat2
#include "cAnimal.h" 
#include <string>

class cCat2 : public cAnimal
{
public:
	// Woof() and Meow()
	void MakeNoise(void);		// Cat's method

	std::string name;	// Common
	float AmountOfBoredom;


};