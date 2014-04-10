/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Phantom.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Phantom.h"

Phantom::Phantom() {}

Phantom::Phantom(const Coordinate& _coordinate, int _team,
			   const string& _name, char _sym, int _life, bool _selected)
: Piece(_coordinate, _team, _name, _sym, _life, _selected) {
	reach = new PhantomReach;
}

Phantom::~Phantom(){}

void Phantom::displayInfo() const{
	Piece::displayInfo();
	cout << "\t\tPossible moves: up to 2 squares in any direction" << endl;
}

Piece* Phantom::clonePiece(const Coordinate& _coord, int _team){
	// This function acts as a semi-copy-constructor instead of implementing one
	// in each of the pieces
	return new Phantom(_coord, _team);
}
