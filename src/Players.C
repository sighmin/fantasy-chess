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

#include "Players.h"

///////////////// PlayerTurn /////////////////
int PlayerTurn::teamTurn = 1;

PlayerTurn::PlayerTurn(){}

PlayerTurn::~PlayerTurn(){}

void PlayerTurn::changeToTeam1(PlayerSwitch*){ // a safety net for programmers
	cout << "Already Team 1's turn." << endl;
}
void PlayerTurn::changeToTeam2(PlayerSwitch*){ // a safety net for programmers
	cout << "Already Team 2's turn." << endl;
}

int PlayerTurn::getTeamTurn() const {
	return teamTurn;
}

void PlayerTurn::setHasSelectedPiece(bool _select) {
	hasSelectedPiece = _select;
}

bool PlayerTurn::getHasSelectedPiece() const {
	return hasSelectedPiece;
}


///////////////// Team1 /////////////////
Team1::Team1(int turn){
	teamTurn = turn;
	hasSelectedPiece = false;
}

Team1::~Team1(){}

void Team1::changeToTeam2(PlayerSwitch* currentTurn){
	
	currentTurn->setTurn(new Team2(2));
	delete this;
}

///////////////// Team2 /////////////////

Team2::Team2(int turn){
	teamTurn = turn;
	hasSelectedPiece = false;
}

Team2::~Team2(){}

void Team2::changeToTeam1(PlayerSwitch* currentTurn){
	
	currentTurn->setTurn(new Team1(1));
	delete this;
}
