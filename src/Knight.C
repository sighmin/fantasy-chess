/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Knight.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Knight.h"

Knight::Knight() {}

Knight::Knight(const Coordinate& _coordinate, int _team, const string& _name, 
			   char _sym, int _life, bool _selected)
: Piece(_coordinate, _team, _name, _sym, _life, _selected) {
	reach = new KnightReach;
}

Knight::~Knight() {}

void Knight::displayInfo() const{
	Piece::displayInfo();
	cout << "\t\tPossible moves: L shapes of 3 + 1 move." << endl;
}

Piece* Knight::clonePiece(const Coordinate& _coord, int _team){
	// This function acts as a semi-copy-constructor instead of implementing one
	// in each of the pieces
	return new Knight(_coord, _team);
}
