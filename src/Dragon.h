/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Dragon.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef DRAGON
#define DRAGON

#include "Piece.h"
using namespace std;

class Dragon : public Piece {
public:
	Dragon();
	Dragon(const Coordinate&, int, const string& s = "Dragon", 
				char sym = 'D', int life = 18, bool b = false);
	~Dragon();
	void displayInfo() const;
	virtual Piece* clonePiece(const Coordinate&, int);
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&) {}
};

#endif
