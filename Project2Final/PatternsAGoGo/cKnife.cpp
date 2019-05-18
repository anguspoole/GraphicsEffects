#include "cKnife.h"
#include <iostream>

cKnife::cKnife()
{
	std::cout << "Knife is created" << std::endl;
	return;
}

cKnife::~cKnife()
{
	std::cout << "Knife is destroyed" << std::endl;
	return;
}
void cKnife::StabbyStab(void)
{
	std::cout << "Knife::Stabb!" << std::endl;
	return;
}

