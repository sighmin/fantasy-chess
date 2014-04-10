/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Game.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Game.h"

Game::Game() {}

Game::~Game() {}

void Game::selectPhase(Coordinate& selectedCoord, Coordinate& requestedCoord){

	// If the coord is the same team, deselect pieces
	if (pieceAtCoord(requestedCoord)) {
		if(pieceAtCoord(requestedCoord)->getTeam() == playerSwitch->playerTurn->getTeamTurn()){
			gameBoard->deselectPieces();
			deselectPlayersPieces();
		}
	}
	// Do validation in a try block
	try {
		selectPiece(requestedCoord);
		gameBoard->display();
		playerSwitch->printCurrentPlayer();
		cout << endl;
		gameBoard->displayTheGraveYard(playerSwitch->playerTurn->getTeamTurn());
		if(pieceAtCoord(requestedCoord)){
			cout << "\nSelected Piece: ";
			pieceAtCoord(requestedCoord)->displayInfo();
			selectedCoord = requestedCoord;
		}					
	} // If an enemy Piece was selected
	catch (GameLogic::SelectEnemyException e) {
		gameBoard->display();
		playerSwitch->printCurrentPlayer();
		cout << endl;
		e.print();
		cout << endl;
		gameBoard->displayTheGraveYard(playerSwitch->playerTurn->getTeamTurn());
		if(gameBoard->getPieceAt(requestedCoord)){
			cout << "\nEnemy Piece stats: ";
			gameBoard->getPieceAt(requestedCoord)->displayInfo();
		}
	} // If no piece was selected
	catch (GameLogic::SelectNULLException e) {
		gameBoard->display();
		playerSwitch->printCurrentPlayer();
		cout << endl;
		e.print();
		cout << endl;
		gameBoard->displayTheGraveYard(playerSwitch->playerTurn->getTeamTurn());
		if(gameBoard->getSelectedPiece()){
			cout << "\nSelected Piece: ";
			gameBoard->getSelectedPiece()->displayInfo();
		}
	}
}

void Game::spellCastPhase(Coordinate& selectedCoord, Coordinate& requestedCoord){
	
	if (playerSwitch->playerTurn->getHasSelectedPiece()) {
		// Do validation in a try block
		try {
			gameBoard->getPieceAt(selectedCoord)->castSpell(selectedCoord, requestedCoord, 
															gameBoard->getPieceAt(selectedCoord),
															gameBoard->getPieceAt(requestedCoord),
															*gameBoard);
			gameBoard->deselectPieces();
			deselectPlayersPieces();
			gameBoard->display();
			playerSwitch->printCurrentPlayer();
			cout << endl;
			gameBoard->displayTheGraveYard(playerSwitch->playerTurn->getTeamTurn());
		}
		catch (char const* msg) {
			gameBoard->display();
			if (kingIsDead < 1) {
				playerSwitch->printCurrentPlayer();
				cout << endl;
				gameBoard->displayTheGraveYard(playerSwitch->playerTurn->getTeamTurn());
			}
			cout << msg << endl;
		}
		
	} else {
		gameBoard->display();
		playerSwitch->printCurrentPlayer();
		cout << "Error: You haven't selected a piece yet.";
		cout << endl;
		gameBoard->displayTheGraveYard(playerSwitch->playerTurn->getTeamTurn());
	}
}

void Game::movePhase(Coordinate& selectedCoord, Coordinate& requestedCoord){
	
	if (playerSwitch->playerTurn->getHasSelectedPiece()) {
		// Do validation in a try block
		try {
			kingIsDead = gameBoard->move(selectedCoord, requestedCoord);
			gameBoard->deselectPieces();
			deselectPlayersPieces();
			gameBoard->refreshSpells();
			gameBoard->display();
			playerSwitch->changeThePlayer(); //if the move was successful, change players
			
			if (kingIsDead < 1) {
				playerSwitch->printCurrentPlayer();
				cout << endl;
				gameBoard->displayTheGraveYard(playerSwitch->playerTurn->getTeamTurn());
			}
		}
		catch (ReachStrategy::MoveException e) {
			gameBoard->display();
			cout << endl;
			e.print();
			if(gameBoard->getSelectedPiece()){
				cout << "\nSelected Piece: ";
				gameBoard->getSelectedPiece()->displayInfo();
			}
		}
	} else {
		gameBoard->display();
		playerSwitch->printCurrentPlayer();
		cout << "Error: You haven't selected a piece yet.";
		cout << endl;
		gameBoard->displayTheGraveYard(playerSwitch->playerTurn->getTeamTurn());
	}
}

