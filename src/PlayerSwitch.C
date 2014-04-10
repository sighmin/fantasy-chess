/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	PlayerSwitch.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "PlayerSwitch.h"

///////////////// PlayerSwitch /////////////////
PlayerSwitch::PlayerSwitch(int s){
	size = s;
	currentPlayer = 1;
	playerTurn = new Team1(1);
	
	// get player names
	int temp = 0;
	string tmpName;

	do {
		cout << "Plese enter team " << (temp % 2) + 1 << ", player " << temp+1 << "'s name\n> ";
		cin >> tmpName;
		playerNames.push_back(tmpName);
		temp++;
	} while (temp < size);
}

PlayerSwitch::~PlayerSwitch() {
	if (playerTurn){
		delete playerTurn;
	}
	playerNames.clear();
}

void PlayerSwitch::changeThePlayer(){
	if (currentPlayer == size){ // this changes the player number (used for printing)
		currentPlayer = 1;
	} else {
		currentPlayer++;
	}

	if(playerTurn->getTeamTurn() == 1){
		playerTurn->changeToTeam2(this);
	} else if(playerTurn->getTeamTurn() == 2){
		playerTurn->changeToTeam1(this);
	}
}

void PlayerSwitch::setTurn(PlayerTurn* turn) {
	playerTurn = turn;
}

void PlayerSwitch::printCurrentPlayer() {
	cout << "Team " << playerTurn->getTeamTurn() << ", ";
	cout << playerNames[currentPlayer-1] << "'s turn." << endl;

}
