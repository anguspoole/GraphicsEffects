#include "cWorld.h"

#include <iostream>

//static 
cWorld* cWorld::m_pTheOneAndOnlyWorld = NULL;


// Return a new world;
cWorld* cWorld::GetTheWorld(void)
{
	//std::cout << x;
	//std::cout << y;
	if ( m_pTheOneAndOnlyWorld == NULL )
	{
		m_pTheOneAndOnlyWorld = new cWorld();
	}
	return m_pTheOneAndOnlyWorld;
}


cWorld::cWorld()
{
	std::cout << "cWorld() created" << std::endl;
}

cWorld::~cWorld()
{
	std::cout << "~cWorld() detroyed" << std::endl;
}

void cWorld::DoThis(void)
{
	std::cout << "cWorld()::DoThis" << std::endl;
}

void cWorld::DoThat(void)
{
	std::cout << "cWorld()::DoThat" << std::endl;
}
