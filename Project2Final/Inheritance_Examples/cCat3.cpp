#include "cCat3.h"

#include <iostream>

void cCat3::MakeNoise(void)		// From cAnimal
{
	std::cout << "Cat3 says meow!" << std::endl;
	return;
}

cCat3::cCat3()
{
	std::cout << "cCat3 is created" << std::endl;
}


cCat3::~cCat3()
{
	std::cout << "cCat3 is destroyed" << std::endl;
}