/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	GameLogic.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef GAMELOGIC
#define GAMELOGIC

#include <iostream>
#include <string>
// ADTs to include //
#include "Coordinate.h"
#include "Board.h"
#include "BoardCreator.h"
#include "CMDInterpreter.h"
using namespace std;

class PlayerSwitch;

class GameLogic {
protected:
	PlayerSwitch* playerSwitch;
	Board* gameBoard;
	BoardCreator* boardCreator;
	CMDInterpreter* interpreter;
	int kingIsDead; // Options 1: team1 lost
					//		   2: team2 lost
					//         3: stalemate
					//		   4: forfeit - team 1
					//		   5: forfeit - team 2
public:
	GameLogic();
	virtual ~GameLogic();
	
//Menu driven functions
	void welcomeMenu();
	void mainMenu();
	void gameMenu();
	void heading();
	
//Input & Creational functions
	void getInput(int&,Coordinate&);
	int getGameOptions();
	void createBoard();
	void createPlayers();
	
//GameLogic logic functions
	void selectPiece(const Coordinate&);
		
//Helper functions
	Piece* pieceAtCoord(const Coordinate&);
	void deselectPlayersPieces();
	
//Template method functions
	void turnCycle();
	virtual void selectPhase(Coordinate&, Coordinate&);
	virtual void spellCastPhase(Coordinate&, Coordinate&);	
	virtual void movePhase(Coordinate&, Coordinate&);

//Exception classes
	class SelectEnemyException {
	private:
		string msg;
	public:
		SelectEnemyException(string s) : msg(s) { }
		void print(){ cout << msg; } 
	};
	
	class SelectNULLException {
	private:
		string msg;
	public:
		SelectNULLException(string s) : msg(s) { }
		void print(){ cout << msg; } 
	};
};

#endif
