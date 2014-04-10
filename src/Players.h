/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Players.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PLAYERS
#define PLAYERS

#include <iostream>
#include "PlayerSwitch.h"

using namespace std;

class PlayerSwitch;

// Holds information about the turns of the players
class PlayerTurn {
public:
	PlayerTurn();
	virtual ~PlayerTurn();
	virtual void changeToTeam1(PlayerSwitch*);
	virtual void changeToTeam2(PlayerSwitch*);
	int getTeamTurn() const;
	void setHasSelectedPiece(bool);
	bool getHasSelectedPiece() const;
	
protected:
	bool hasSelectedPiece;
	static int teamTurn;
};

// The following classes are the 'Concrete players' required
class Team1 : public PlayerTurn {

public:
	Team1(int);
	~Team1();
	void changeToTeam2(PlayerSwitch*);
};

class Team2 : public PlayerTurn {

public:
	Team2(int);
	~Team2();
	void changeToTeam1(PlayerSwitch*);

};

#endif
