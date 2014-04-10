/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Knight.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef KNIGHT
#define KNIGHT

#include "Piece.h"
using namespace std;

class Knight : public Piece {
public:
	Knight();
	Knight(const Coordinate&, int, const string& s = "Knight", 
				char sym = 'K', int life = 10, bool b = false);
	~Knight();
	void displayInfo() const;
	virtual Piece* clonePiece(const Coordinate&, int);
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&) {}
};

#endif
