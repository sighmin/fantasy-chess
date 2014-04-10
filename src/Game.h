/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Game.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef GAME
#define GAME

#include "GameLogic.h"
#include "Players.h"
using namespace std;

//class PlayerSwitch;

class Game : public GameLogic {
public:
	Game();
	~Game();
	
	// Primative Operators
	void selectPhase(Coordinate&, Coordinate&);
	void spellCastPhase(Coordinate&, Coordinate&);	
	void movePhase(Coordinate&, Coordinate&);
	
};

#endif
