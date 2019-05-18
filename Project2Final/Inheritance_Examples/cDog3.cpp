#include "cDog3.h"

#include <iostream>

void cDog3::MakeNoise(void)		// From cAnimal
{
	std::cout << "Dog3 says woof!" << std::endl;
	return;
}


cDog3::cDog3()
{
	std::cout << "cDog3 is created" << std::endl;
}

// Copy constructor
cDog3::cDog3(const cDog3 &old_obj)
{
	std::cout << "cDog3 is created (copy constructor)" << std::endl;
}


cDog3::~cDog3()
{
	std::cout << "cDog3 is destroyed" << std::endl;
}