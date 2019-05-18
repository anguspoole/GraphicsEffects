#include "cDog1.h"

#include <iostream>

void cDog1::Woof(void)
{
	std::cout << "Dog says Woof!" << std::endl;
	std::cout << this->colour << std::endl;
	return;
}