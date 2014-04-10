/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	ReachStrategy.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef REACH
#define REACH

#include "Coordinate.h"
#include <cmath>
#include <iostream>
using namespace std;

class Piece;
//class Game;

// Abstract strategy
class ReachStrategy {
protected:
	int straight;
	int diagonal;
	void calcXYMovement(int&,int&,const Coordinate&, const Coordinate&);
public:
	ReachStrategy(int, int);
	virtual ~ReachStrategy();
	virtual void validateReach(const Coordinate&, const Coordinate&) = 0;
	
	class MoveException {
	private:
		string msg;
	public:
		MoveException(string s) : msg(s) { }
		void print(){ cout << msg; } 
	};
};

class FootSoldierReach : public ReachStrategy {
public:
	FootSoldierReach(int _straight = 2, int _diagonal = 2);
	void validateReach(const Coordinate&, const Coordinate&);
};

class KnightReach : public ReachStrategy {
private:
	int lShape;
public:
	KnightReach(int _straight = 3, int _lShape = 1);
	void validateReach(const Coordinate&, const Coordinate&);
};

class KingReach : public ReachStrategy {
public:
	KingReach(int _straight = 3, int _diagonal = 3);
	void validateReach(const Coordinate&, const Coordinate&);
};

class DragonReach : public ReachStrategy {
public:
	DragonReach(int _straight = 3, int _diagonal = 0);
	void validateReach(const Coordinate&, const Coordinate&);
};

class PhantomReach : public ReachStrategy {
public:
	PhantomReach(int _straight = 2, int _diagonal = 2);
	void validateReach(const Coordinate&, const Coordinate&);
};

class NecromancerReach : public ReachStrategy {
public:
	NecromancerReach(int _straight = 1, int _diagonal = 1);
	void validateReach(const Coordinate&, const Coordinate&);
};

class HealerReach : public ReachStrategy {
public:
	HealerReach(int _straight = 0, int _diagonal = 5);
	void validateReach(const Coordinate&, const Coordinate&);
};

#endif
