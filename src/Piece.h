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

#ifndef PIECE
#define PIECE

#include <string>
#include "ReachStrategy.h"
#include "Coordinate.h"
using namespace std;

class ReachStrategy;
class Coordinate;
class Board;

// Prototype
class Piece {
protected:
	string name;
	char symbol;
	int maxLife;
	int life;
	int team;
	bool selected;
	ReachStrategy* reach;
	Coordinate coordinate;
	virtual void setLife(int);
	virtual void decLife(int);
	
public:
	Piece();//   coord      team    name       sym    life&maxLife  selected
	Piece(const Coordinate&, int, const string&, char,    int,       bool);
	virtual ~Piece();
// Accessors
	virtual string getName() const;
	virtual char getSymbol() const;
	virtual int getLife() const;
	virtual int getTeam() const;
	virtual bool isSelected() const;
	virtual Coordinate getCoord() const;
	virtual ReachStrategy* getReach() const;
	virtual int getMaxLife() const;
	virtual void displayOnBoard() const;
	
// Mutators
	/*virtual void setName(const string&);
	virtual void setSymbol(char);		// For extending the game to customly create pieces
	virtual void setTeam(int);*/		// (bonus section), the store
	virtual void setSelected(bool);
	virtual void setCoord(const Coordinate&);
	virtual void refresh();
	
// Helper functions
	virtual void displayInfo() const;
	virtual Piece* clonePiece(const Coordinate&, int) = 0;
	virtual void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&) = 0;
	
// Friends
	friend class Heal;
	friend class Resurrect;
	friend class FireBreathing;
	friend class Teleport;
	friend class SpellDecorator;
	friend class TwoDBoard;
	
};

#endif



