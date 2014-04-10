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

#include "Necromancer.h"

Necromancer::Necromancer() {}

Necromancer::Necromancer(const Coordinate& _coordinate, int _team, const string& _name, 
		   char _sym, int _life, bool _selected)
: Piece(_coordinate, _team, _name, _sym, _life, _selected) {
	reach = new NecromancerReach;
}

Necromancer::~Necromancer() {}

void Necromancer::displayInfo() const{
	Piece::displayInfo();
	cout << "\t\tPossible moves: 1 square in any direction." << endl;
}

Piece* Necromancer::clonePiece(const Coordinate& _coord, int _team){
	// This function acts as a semi-copy-constructor instead of implementing one
	// in each of the pieces
	return new Necromancer(_coord, _team);
}
