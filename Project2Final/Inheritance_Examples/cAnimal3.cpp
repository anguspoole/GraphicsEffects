#include "cAnimal3.h"

#include <iostream>

void cAnimal3::MakeNoise(void)
{
	std::cout << "cAnimal3: MakeNoise()!!" << std::endl;
	return;
}

cAnimal3::cAnimal3()
{
	std::cout << "cAnimal is created" << std::endl;
}


cAnimal3::~cAnimal3()
{
	std::cout << "cAnimal is destroyed" << std::endl;
}