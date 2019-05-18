#include <iostream>

unsigned long long numberOfCalls = 0;

const unsigned int SIZEOFCACHE = 1000;

// Note I'm clearing the array to all zeros 
// (which you can only do with integers)
unsigned long long fibNumberCache[SIZEOFCACHE] = {0};

unsigned long long calcFib( unsigned int number )
{
	numberOfCalls++;

	if ( number == 0 )
	{
		return 0;		// F(0) = 0
	}
	if ( number == 1 )
	{
		return 1;		// F(1) = 1
	}

	// Have we already got a number? 
	if ( fibNumberCache[number] != 0 )
	{
		return fibNumberCache[number];
	}
	else
	{
		// Have to calculate it... sorry
		unsigned long long fibNum = calcFib( number - 1 ) + calcFib( number - 2 );

		// Save it for later
		fibNumberCache[number] = fibNum;

		return fibNum;
	}

}

int main()
{

	for ( int num = 0; num != 100; num++ )
	{
		numberOfCalls = 0;
		std::cout 
			<< "Fib(" << num << ") = " 
			<< calcFib(num) 
			<< "  took: " << numberOfCalls 
			<< std::endl;
	}

	return 0;
}


class cChange
{
public:
	int pennies;		int nickels;
	int dimes;			int quarters; 
	int loonies;		int twonies;
	int fives;			int tens;
	int twenties;		int fifties;	
	int hundreds;
};

cChange calculateMinChange( int totalInCents, cChange &changeSoFar )
{ 
	cChange toReturn;
	if ( totalInCents < 5 )
	{
		toReturn.pennies = totalInCents;
	}
	else if ( totalInCents < 10 )
	{
		toReturn.nickels = 1;
		toReturn.pennies = totalInCents - 5;
	}


	return toReturn;
}
