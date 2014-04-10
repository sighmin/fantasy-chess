/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
*	FileName	Necromancer.C
*  
*	Authors		Dean Marsden		29143332
*			Simon van Dyk		10266764
*
*	Date		October 2010
*	
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef NECROMANCER
#define NECROMANCER

#include "Piece.h"
using namespace std;

class Necromancer : public Piece {
public:
	Necromancer();
	Necromancer(const Coordinate&, int, const string& s = "Necromancer", 
		 char sym = 'N', int life = 6, bool b = false);
	~Necromancer();
	void displayInfo() const;
	virtual Piece* clonePiece(const Coordinate&, int);
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&) {}
};

#endif
