/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	SetupStrategy.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SETUPSTRATEGY
#define SETUPSTRATEGY

#include "FootSoldier.h"
#include "Knight.h"
#include "King.h"
#include "Dragon.h"
#include "Phantom.h"
#include "Healer.h"
#include "Necromancer.h"

#include "Coordinate.h"
#include "SpellDecorator.h"

#include <time.h> //for time()
#include <stdlib.h> //for srand() and rand()
#include <iostream>
using namespace std;

class SetupStrategy {
protected:
	Piece** pieceTypes;
public:
	SetupStrategy();
	virtual ~SetupStrategy();
	virtual void setup(Piece***,int) = 0;
};

class FixedSetupStrategy : public SetupStrategy {
public:
	void setup(Piece***,int);
};

class RandomSetupStrategy : public SetupStrategy {
public:
	void setup(Piece***,int);
	int randomY(int,int);
	int randomX(int);
};

#endif
