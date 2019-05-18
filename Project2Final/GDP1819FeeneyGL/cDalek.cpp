#include "cDalek.h"

#include <process.h>
#include <Windows.h>		// For CRITICAL_SECTION, CreateThread, ResumeThread, etc.

#include "cRandThreaded.h"
#include "cDalekManagerTripleBuffer.h"


//The actual win32 thread function
// EVERY dalek calls this function but on an different thread
DWORD WINAPI DalekBrainThread(void* pInitialData)
{
	// Deref the this pointer to get at the specific Dalek

	cDalek* pDalek = (cDalek*)pInitialData;

	// Delay the start for about 250 ms
	Sleep(250);

	// Now endlessly run the loop until it's time to exit
	if ( pDalek->bIsAlive )
	{
		pDalek->Update();

		// Release control of the thread
		Sleep(0);

	}//pDalek->bIsAlive


	return 0;
}

cDalek::cDalek()
{
	this->bIsAlive = true;
	this->m_dalekIndex = 0;
	this->m_pDalekManager = NULL;

	this->m_pLocalTimer = new CHRTimer();
	this->m_pLocalTimer->Reset();
	return;
}

void cDalek::CreateThreadAndStartUpdating( unsigned int dalekIndex, 
										   cDalekManagerTripleBuffer* pDalekManager, 
										   cRandThreaded* pRandThread )
{
	this->m_dalekIndex = dalekIndex;

	this->m_pDalekManager = pDalekManager;

	this->m_pRandThread = pRandThread;

	LPDWORD phThread = 0;	// Clear to zero
	DWORD hThread = 0;	
	HANDLE hThreadHandle = 0;
	
	// Pass a pointer to this instance 
	// Recal that the "this" pointer is the pointer to
	//	this particular instance of the object
	void* pThisDalek = (void*)(this);

	hThreadHandle = CreateThread(NULL,	// Default security
								0,		// Stack size - default - win32 = 1 Mbyte
								&DalekBrainThread, // Pointer to the thread's function
								pThisDalek,		// The value (parameter) we pass to the thread
									// This is a pointer to void... more on this evil thing later...
								0,  // CREATE_SUSPENDED or 0 for threads...
								(DWORD*) &phThread);		// pointer or ref to variable that will get loaded with threadID

	return;
}

void cDalek::ResetTimerAndStart(void)
{
	this->m_pLocalTimer->ResetAndStart();
	return;
}

// Will pick a random direction and move for x seconds
void cDalek::PickNewDirection(void)
{
	glm::vec3 newRelativeDestination;

	newRelativeDestination.x = (float)this->m_pRandThread->getNextRandDouble();
	newRelativeDestination.y = (float)this->m_pRandThread->getNextRandDouble();
	newRelativeDestination.z = (float)this->m_pRandThread->getNextRandDouble();

	// Pick a random time between 1 and 5 seconds
	this->m_MoveCountDown = (float)this->m_pRandThread->getNextRandDouble() * 4.0f + 1.0f;

	this->m_Velocity = newRelativeDestination / this->m_MoveCountDown;

	return;
}


void cDalek::Update(void)
{
	float deltaTime = this->m_pLocalTimer->GetElapsedSecondsAverage();


	glm::vec3 deltaVel = this->m_Velocity * deltaTime;
	
	this->m_position += deltaVel;

	this->m_MoveCountDown -= deltaTime;

	if ( this->m_MoveCountDown <= 0.0f )
	{
		this->PickNewDirection();
	}

	return;
}
