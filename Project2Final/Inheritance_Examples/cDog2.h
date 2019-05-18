#pragma once
// cDog2
#include "cAnimal.h" 
#include <string>

class cDog2 : public cAnimal
{
public:
	// Woof() and Meow()
	void MakeNoise(void);		// From cAnimal

	int size;
	std::string colour;

};