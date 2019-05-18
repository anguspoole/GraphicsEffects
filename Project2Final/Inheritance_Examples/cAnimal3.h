#ifndef _cAnimal_HG_
#define _cAnimal_HG_

class cAnimal3
{
public:
	cAnimal3();
	virtual ~cAnimal3();

	// Woof() and Meow()
	// virtual makes this polymorphic (vtable)
	virtual void MakeNoise(void);
};

#endif