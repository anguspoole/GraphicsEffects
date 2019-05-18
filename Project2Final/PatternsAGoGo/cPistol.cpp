#include "cPistol.h"
#include <iostream>

cPistol::cPistol()
{
	std::cout << "cPistol is created" << std::endl;
	return;
}

cPistol::~cPistol()
{
	std::cout << "cPistol is destroyed" << std::endl;
	return;
}
void cPistol::Shoot(void)
{
	std::cout << "cPistol::Bang!" << std::endl;
	return;
}

