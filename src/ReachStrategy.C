/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	ReachStrategy.C
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "ReachStrategy.h"

///////////////// Reach /////////////////

ReachStrategy::ReachStrategy(int _straight, int _diagonal)
						: straight(_straight), diagonal(_diagonal) {}

ReachStrategy::~ReachStrategy() {}

void ReachStrategy::calcXYMovement(int& xMovement, int& yMovement, const Coordinate& currentCoord, const Coordinate& destinationCoord){
	xMovement = abs((double)(destinationCoord.getX() - currentCoord.getX()));
	yMovement = abs((double)(destinationCoord.getY() - currentCoord.getY()));
}

///////////////// FootSoldierReach /////////////////
FootSoldierReach::FootSoldierReach(int _straight, int _diagonal) : ReachStrategy(_straight, _diagonal) {}

void FootSoldierReach::validateReach(const Coordinate& currentCoord, const Coordinate& destinationCoord){
	int xMovement, yMovement;
	calcXYMovement(xMovement, yMovement, currentCoord, destinationCoord);
	// Check straight
	if ((xMovement <= straight && yMovement == 0)
		|| (yMovement <= straight && xMovement == 0)){
		return;
	}
	// Check diagonal
	if ((xMovement == yMovement) && (xMovement + yMovement <= diagonal*2)) {
		return;
	}
	// If it doesn't satisfy the ifs, throw exception for invalid movement
	throw MoveException("Invalid move: you can't move there.");
}

///////////////// KnightReach /////////////////
KnightReach::KnightReach(int _straight, int _diagonal) : ReachStrategy(_straight, _diagonal) {
	lShape = 1;
}

void KnightReach::validateReach(const Coordinate& currentCoord, const Coordinate& destinationCoord){
	int xMovement, yMovement;
	calcXYMovement(xMovement, yMovement, currentCoord, destinationCoord);
	
	// Check straight
	if ((xMovement == straight && yMovement == 1)
		|| (yMovement == straight && xMovement == 1)){
		return;
	}
	throw MoveException("Invalid move: you can't move there.");
}

///////////////// KingReach /////////////////
KingReach::KingReach(int _straight, int _diagonal) : ReachStrategy(_straight, _diagonal) {}

void KingReach::validateReach(const Coordinate& currentCoord, const Coordinate& destinationCoord){
	int xMovement, yMovement;
	calcXYMovement(xMovement, yMovement, currentCoord, destinationCoord);
	// Check straight
	if ((xMovement <= straight && yMovement == 0)
		|| (yMovement <= straight && xMovement == 0)){
		return;
	}
	// Check diagonal
	if ((xMovement == yMovement) && (xMovement + yMovement <= diagonal*2)) {
		return;
	}
	// If it doesn't satisfy the ifs, throw exception for invalid movement
	throw MoveException("Invalid move: you can't move there.");
}

///////////////// DragonReach /////////////////
DragonReach::DragonReach(int _straight, int _diagonal) : ReachStrategy(_straight, _diagonal) {}

void DragonReach::validateReach(const Coordinate& currentCoord, const Coordinate& destinationCoord){
	int xMovement, yMovement;
	calcXYMovement(xMovement, yMovement, currentCoord, destinationCoord);
	// Check straight
	if ((xMovement <= straight && yMovement == 0)
		|| (yMovement <= straight && xMovement == 0)){
		return;
	}
	// If it doesn't satisfy the ifs, throw exception for invalid movement
	throw MoveException("Invalid move: you can't move there.");
}

///////////////// PhantomReach /////////////////
PhantomReach::PhantomReach(int _straight, int _diagonal) : ReachStrategy(_straight, _diagonal) {}

void PhantomReach::validateReach(const Coordinate& currentCoord, const Coordinate& destinationCoord){
	int xMovement, yMovement;
	calcXYMovement(xMovement, yMovement, currentCoord, destinationCoord);
	// Check straight
	if ((xMovement <= straight && yMovement == 0)
		|| (yMovement <= straight && xMovement == 0)){
		return;
	}
	// Check diagonal
	if ((xMovement == yMovement) && (xMovement + yMovement <= diagonal*2)) {
		return;
	}
	// If it doesn't satisfy the ifs, throw exception for invalid movement
	throw MoveException("Invalid move: you can't move there.");
}

///////////////// NecromancerReach /////////////////
NecromancerReach::NecromancerReach(int _straight, int _diagonal) : ReachStrategy(_straight, _diagonal) {}

void NecromancerReach::validateReach(const Coordinate& currentCoord, const Coordinate& destinationCoord){
	int xMovement, yMovement;
	calcXYMovement(xMovement, yMovement, currentCoord, destinationCoord);
	// Check straight
	if ((xMovement <= straight && yMovement == 0)
		|| (yMovement <= straight && xMovement == 0)){
		return;
	}
	// Check diagonal
	if ((xMovement == yMovement) && (xMovement + yMovement <= diagonal*2)) {
		return;
	}
	// If it doesn't satisfy the ifs, throw exception for invalid movement
	throw MoveException("Invalid move: you can't move there.");
}

///////////////// HealerReach /////////////////
HealerReach::HealerReach(int _straight, int _diagonal) : ReachStrategy(_straight, _diagonal) {}

void HealerReach::validateReach(const Coordinate& currentCoord, const Coordinate& destinationCoord){
	int xMovement, yMovement;
	calcXYMovement(xMovement, yMovement, currentCoord, destinationCoord);

	// Check diagonal
	if ((xMovement == yMovement) && (xMovement + yMovement <= diagonal*2)) {
		return;
	}
	// If it doesn't satisfy the ifs, throw exception for invalid movement
	throw MoveException("Invalid move: you can't move there.");
}
