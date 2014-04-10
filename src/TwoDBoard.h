/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	TwoDBoard.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TWODBOARD
#define TWODBOARD

#include "Board.h"
#include "SpellDecorator.h"
using namespace std;

class TwoDBoard : public Board {
public:
	TwoDBoard();
	virtual ~TwoDBoard();
	
//Display
	void display() const;
	
//Overloaded operators
	Piece* operator()(const Coordinate&);
	Piece* operator()(int, int);
	
//Helper functions
	Piece* getSelectedPiece() const;
	Piece* getPieceAt(const Coordinate&);
	void setPieceAt(const Coordinate&, Piece*);
	void swapPiecesAt(Coordinate&, Coordinate&);
	void buryPiece(const Coordinate&);
	
//Logic functions
	int move(Coordinate&, Coordinate&);
	void movePieces(Coordinate&, Coordinate&);
	void attackPiece(Coordinate&, Coordinate&);
	
	void deselectPieces();
	void refreshSpells();
	
	void calculateScores(const int);
	
//Friend classes
	friend class Resurrect;
	
};

#endif
