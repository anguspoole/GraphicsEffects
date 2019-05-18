#pragma once
// cDog3
#include "cAnimal3.h" 

#include <string>

//class cSuperDog;

class cDog3 : public cAnimal3
{
public:
	cDog3();
	// Copy constructor
	cDog3(const cDog3 &old_obj); 
	virtual ~cDog3();
	// Woof() and Meow()
	virtual void MakeNoise(void);		// From cAnimal

//	friend cSuperDog;

protected:
	int size;		// Visible to all der classes
private:	
	std::string colour;	// private

};