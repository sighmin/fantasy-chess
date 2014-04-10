/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	King.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef KING
#define KING

#include "Piece.h"
using namespace std;

class King : public Piece {
public:
	King();
	King(const Coordinate&, int, const string& s = "King", 
		   char sym = 'X', int life = 30, bool b = false);
	~King();
	void displayInfo() const;
	virtual Piece* clonePiece(const Coordinate&, int);
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&) {}
};

#endif
