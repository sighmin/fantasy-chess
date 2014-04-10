/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *	FileName	SpellDecorator.h
 *  
 *	Authors		Dean Marsden		29143332
 *			Simon van Dyk		10266764
 *
 *	Date		October 2010
 *	
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SPELLDECORATOR
#define SPELLDECORATOR
#include "Piece.h"

using namespace std;

class Board;

class SpellDecorator : public Piece {
protected:	
	Piece* pieceSpell; // Piece that the spell 'wraps'
	bool mana;
	void setLife(int);
	void decLife(int);
	
public:
	SpellDecorator(Piece*);
	virtual ~SpellDecorator();
	virtual void validateSpellReach(const Coordinate&, const Coordinate&, Piece*, Piece*);
	
// Accessors
	string getName() const;
	char getSymbol() const;
	int getLife() const;
	int getTeam() const;
	bool isSelected() const;
	Coordinate getCoord() const;
	ReachStrategy* getReach() const;
	int getMaxLife() const;
	void displayOnBoard() const;
	virtual void displayInfo() const;
	
// Mutators
	/*void setName(const string&);  // For extending the game to customly create pieces
	void setSymbol(char);			// (bonus section), the store
	void setTeam(int);*/
	void setSelected(bool);
	void setCoord(const Coordinate&);
	void refresh();
};

//Dragon's Spell
class FireBreathing : public SpellDecorator {
public:
	FireBreathing(Piece*);
	Piece* clonePiece(const Coordinate&, int);
	void displayInfo() const;
	
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&);
	void validateSpellReach(const Coordinate&, const Coordinate&, Piece*, Piece*);
};

//King's Spell
class KingTeleport : public SpellDecorator {
private:
	bool teleportDust;
public:
	KingTeleport(Piece*);
	Piece* clonePiece(const Coordinate&, int);
	void displayInfo() const;
	
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&);
	void validateSpellReach(const Coordinate&, const Coordinate&, Piece*, Piece*);
};

//Phantom's Spell
class Teleport : public SpellDecorator {
public:
	Teleport(Piece*);
	Piece* clonePiece(const Coordinate&, int);
	void displayInfo() const;
	
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&);
	void validateSpellReach(const Coordinate&, const Coordinate&, Piece*, Piece*);
};

//Necromancer's Spell
class Resurrect : public SpellDecorator {
public:
	Resurrect(Piece*);
	Piece* clonePiece(const Coordinate&, int);
	void displayInfo() const;
	
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&);
	void validateSpellReach(const Coordinate&, const Coordinate&, Piece*, Piece*);
};

//Healer's Spell
class Heal : public SpellDecorator {
public:
	Heal(Piece*);
	Piece* clonePiece(const Coordinate&, int);
	void displayInfo() const;
	
	void castSpell(Coordinate&, Coordinate&, Piece*, Piece*, Board&);
	void validateSpellReach(const Coordinate&, const Coordinate&, Piece*, Piece*);	
};

#endif
