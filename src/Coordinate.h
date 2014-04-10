/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	Coordinate.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef COORDINATE
#define COORDINATE

#include <iostream>
using namespace std;

class Coordinate {
private:
	int x;
	int y;
public:
	Coordinate(int = 0,int = 0);
	Coordinate(const Coordinate&);
	
//Accessors
	int getX() const;
	int getY() const;
	Coordinate getCoordXY() const;
	
//Mutators
	void setX(int);
	void setY(int);
	void setCoordXY(int ,int);
	void setCoordXY(Coordinate);
	
//Used by board
	Coordinate& operator=(const Coordinate&);
	
//Used for testing
	friend ostream& operator<<(ostream&, const Coordinate&);
};

#endif
