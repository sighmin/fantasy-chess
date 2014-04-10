/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*	FileName	Healer.h
*  
*	Authors		Dean Marsden		29143332
*			Simon van Dyk		10266764
*
*	Date		October 2010
*	
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef HEALER
#define HEALER

#include "Piece.h"
using namespace std;

class Healer : public Piece {
public:
	Healer();
	Healer(const Coordinate&, int, const string& s = "Healer", 
		 char sym = 'H', int life = 6, bool b = false);
	~Healer();
	void displayInfo() const;
	virtual Piece* clonePiece(const Coordinate&, int);
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&) {}
};

#endif
