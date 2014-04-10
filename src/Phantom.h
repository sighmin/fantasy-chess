/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Phantom.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PHANTOM
#define PHANTOM

#include "Piece.h"
using namespace std;

class Phantom : public Piece {
public:
	Phantom();
	Phantom(const Coordinate&, int, const string& s = "Phantom", 
		   char sym = 'P', int life = 5, bool b = false);
	~Phantom();
	void displayInfo() const;
	virtual Piece* clonePiece(const Coordinate&, int);
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&) {}
};

#endif
