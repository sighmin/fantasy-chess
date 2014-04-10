/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Board.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef BOARD
#define BOARD

#include <vector>
#include <stack>
#include <typeinfo>
//ADTs to include
#include "Piece.h"
#include "PStack.h"
#include "SetupStrategy.h"
using namespace std;

class Board {
protected:
	static const int DEFAULT_DIMENSIONS;
	Piece*** board;
	SetupStrategy* strategy;
	vector<Piece*> graveyard;
	PStack team1GraveYard;
	PStack team2GraveYard;
	
public:
	Board();
	virtual ~Board();
	
//Display
	virtual void display() const = 0;
	
//Strategy functions
	void setStrategy(int);
	void setupBoard();
	
//Helper functions
	virtual Piece* operator()(int, int) = 0;
	virtual Piece* operator()(const Coordinate&) = 0;
	virtual Piece* getPieceAt(const Coordinate&) = 0;
	virtual void setPieceAt(const Coordinate&, Piece*) = 0;
	virtual Piece* getSelectedPiece() const = 0;
	virtual void swapPiecesAt(Coordinate&, Coordinate&) = 0;
	virtual void displayTheGraveYard(int);
	
//Logic functions
	virtual int move(Coordinate&, Coordinate&);
	virtual void movePieces(Coordinate&, Coordinate&);
	virtual void attackPiece(Coordinate&, Coordinate&);
	virtual void buryPiece(const Coordinate&);
	virtual void refreshSpells();
	virtual void calculateScores(const int);
	virtual void deselectPieces();

//Friend classes
	friend class Resurrect;
};

#endif
