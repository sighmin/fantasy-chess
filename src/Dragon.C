/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Dragon.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Dragon.h"

Dragon::Dragon() {}

Dragon::Dragon(const Coordinate& _coordinate, int _team,
						 const string& _name, char _sym, int _life, bool _selected)
: Piece(_coordinate, _team, _name, _sym, _life, _selected) {
	reach = new DragonReach;
}

Dragon::~Dragon(){}

void Dragon::displayInfo() const{
	Piece::displayInfo();
	cout << "\t\tPossible moves: up to 3 squares in any row or column" << endl;
}

Piece* Dragon::clonePiece(const Coordinate& _coord, int _team){
	// This function acts as a semi-copy-constructor instead of implementing one
	// in each of the pieces
	return new Dragon(_coord, _team);
}
