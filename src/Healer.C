/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* 	FileName	Healer.C
*  
*	Authors		Dean Marsden		29143332
*			Simon van Dyk		10266764
*
*	Date		October 2010
*	
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Healer.h"

Healer::Healer() {}

Healer::Healer(const Coordinate& _coordinate, int _team, const string& _name, 
		   char _sym, int _life, bool _selected)
: Piece(_coordinate, _team, _name, _sym, _life, _selected) {
	reach = new HealerReach;
}

Healer::~Healer() {}

void Healer::displayInfo() const{
	Piece::displayInfo();
	cout << "\t\tPossible moves: 5 squares in diagonals." << endl;
}

Piece* Healer::clonePiece(const Coordinate& _coord, int _team){
	// This function acts as a semi-copy-constructor instead of implementing one
	// in each of the pieces
	return new Healer(_coord, _team);
}
