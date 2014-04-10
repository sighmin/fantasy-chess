/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	PlayerSwitch.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PLAYERSWITCH
#define PLAYERSWITCH

#include <iostream>
#include <vector>
#include "Players.h"
#include "PStack.h"

using namespace std;

class PlayerTurn;

class PlayerSwitch {
private:
	int size;		// # of players
	int currentPlayer; // holds current player #
	vector<string> playerNames;
public:
	PlayerSwitch(int);
	~PlayerSwitch();

	void setTurn(PlayerTurn*);
	void changeThePlayer();
	void printCurrentPlayer();
	
	PlayerTurn* playerTurn;

};

#endif
