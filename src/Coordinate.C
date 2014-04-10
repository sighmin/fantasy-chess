/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Coordinate.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Coordinate.h"

Coordinate::Coordinate(int _x, int _y) : x(_x), y(_y) { }

//Copy Constructor 
Coordinate::Coordinate(const Coordinate& coord){
	x = coord.getX();
	y = coord.getY();
}

//Accessors
int Coordinate::getX() const{
	return x;
}
int Coordinate::getY() const{
	return y;
}
Coordinate Coordinate::getCoordXY() const{
	Coordinate tmp(x,y);
	return tmp;
}

//Mutators
void Coordinate::setX(int _x){
	x = _x;
}
void Coordinate::setY(int _y){
	y = _y;
}
void Coordinate::setCoordXY(int _x, int _y){
	x = _x;
	y = _y;
}
void Coordinate::setCoordXY(Coordinate coord){
	x = coord.getX();
	y = coord.getY();
}

//Used in board
Coordinate& Coordinate::operator=(const Coordinate& rhs){
	if (this != &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
	}
	return *this;
}

//Used for testing
ostream& operator<<(ostream& ostrm, const Coordinate& coord){
	ostrm << '(' << coord.getX() << " ," << coord.getY() << ')';
	return ostrm;
}

