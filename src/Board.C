/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Board.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Board.h"

const int Board::DEFAULT_DIMENSIONS = 9;

enum StrategyType{ _FIXED = 1, _RANDOM = 2 };

Board::Board(){
	strategy = 0;
	board = 0;
}

Board::~Board() {  
	if (strategy){
		delete strategy;
	}
}

void Board::setStrategy(int type){  
	if (strategy){
		delete strategy;
	}
	if (type == _FIXED){
		strategy = new FixedSetupStrategy();
	} else if (type == _RANDOM){
		strategy = new RandomSetupStrategy();
	}
}

void Board::setupBoard(){
	strategy->setup(board, DEFAULT_DIMENSIONS);
}

int Board::move(Coordinate&, Coordinate&) {
	return 0;
}

void Board::displayTheGraveYard(int team) {
	if (team == 1) {
		team1GraveYard.displayStack();
	} else {
		team2GraveYard.displayStack();
	}
}

// Virtual functions being re-defined
void Board::calculateScores(const int) { }

void Board::deselectPieces() { }

void Board::movePieces(Coordinate&, Coordinate&) { }

void Board::attackPiece(Coordinate&, Coordinate&) { }

void Board::buryPiece(const Coordinate&) { }

void Board::refreshSpells() { }













