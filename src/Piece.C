/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Piece.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Piece.h"

Piece::Piece() {}

Piece::Piece(const Coordinate& _coordinate, int _team, const string& _name, 
			 char _sym, int _life, bool _selected)
: name(_name), symbol(_sym), maxLife(_life),
life(_life), selected(_selected), coordinate(_coordinate) {
	team = _team;
	reach = 0;
}

Piece::~Piece(){
	if (reach){
		delete reach;
		reach = 0;
	}
}

// Accessors
string Piece::getName() const{
	return name;
}
char Piece::getSymbol() const{
	return symbol;
}
int Piece::getLife() const{
	return life;
}
int Piece::getTeam() const{
	return team;
}
bool Piece::isSelected() const{
	return selected;
}
Coordinate Piece::getCoord() const{
	return coordinate;
}
ReachStrategy* Piece::getReach() const{
	return reach;
}
int Piece::getMaxLife() const{
	return maxLife;
}
void Piece::displayOnBoard() const{
	cout << symbol << team;
}

// Mutators
/*void Piece::setName(const string& _name){// For extending the game to customly create pieces
	name = _name;					   	// (bonus section), the store
}
void Piece::setSymbol(char _symbol){
	symbol = _symbol;
}
void Piece::setTeam(int _team){
	team = _team;
}*/
void Piece::setLife(int _life){
	if (_life > maxLife) {// so you can't restore a piece to greater than his max
		life = maxLife;
	} else {
		life = _life;		
	}
}
void Piece::setSelected(bool _selected){
	selected = _selected;
}
void Piece::setCoord(const Coordinate& coord){
	coordinate.setCoordXY(coord.getX(), coord.getY());
}
void Piece::decLife(int damage){
	life -= damage;
}
void Piece::refresh(){}

// Helper functions
void Piece::displayInfo() const {
	cout << name << ", " << symbol << team << endl;
	cout << "\t\tLife remaining: " << life << endl;
}
















