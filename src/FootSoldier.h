/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	FootSoldier.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef FOOTSOLDIER
#define FOOTSOLDIER

#include "Piece.h"
using namespace std;

class FootSoldier : public Piece {
public:
	FootSoldier();
	FootSoldier(const Coordinate&, int, const string& s = "FootSoldier", 
				char sym = 'F', int life = 6, bool b = false);
	~FootSoldier();
	void displayInfo() const;
	virtual Piece* clonePiece(const Coordinate&, int);
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&) {}
};

#endif
