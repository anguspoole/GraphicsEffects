#ifndef _cWorld_HG_
#define _cWorld_HG_

// 1. Make on global
// 2. Make it global and static
// 3. Make constructor private
// 4. Make a pointer to the class inside the class and private
// 5. Make a "factory method" that reutrn the pointer
// 6. Inside the factory method, check if I've already
//    make the class (called new). If not, call new.
//    If I have, then return the (existing) pointer
// 7. Make the pointer variable static
// 8. Make the factory method static, too
// 9. Declare the actual pointer variable in the CPP file

class cWorld 
{
public:
	~cWorld();

static int x;		// ONLY ONE!
	int y;

	// Return a new world (factory method)
	// Static methods are only allowed to look at 
	//	static variables.
	static cWorld* GetTheWorld(void);

	void DoThis(void);
	void DoThat(void);
private:
	cWorld();		// new()

	// static AREN'T in the header!!!! (sorry)
	static cWorld* m_pTheOneAndOnlyWorld;

	int Hello;
};

#endif
