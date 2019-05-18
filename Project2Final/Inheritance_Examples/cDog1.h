#ifndef _cDog_HG_
#define _cDog_HG_
#include <string>

class cDog1 
{
public:
	void Woof(void);

	std::string name;	// Common

	int size;
	std::string colour;

	int getAnimalType(void)
	{
		return 2;
	}
};

#endif 

